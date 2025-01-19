#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

// Definição dos pinos dos LEDs e buzzer
#define LED_RED_PIN 13   // LED vermelho
#define LED_BLUE_PIN 12  // LED azul
#define LED_GREEN_PIN 11 // LED verde
#define BUZZER_PIN 21    // Buzzer
#define BUZZER_FREQ_HZ 3200 // Configuração da frequência do buzzer (em Hz)
#define HIGH 4096
#define LOW 0

// Definição dos pinos do teclado
uint columns[4] = {4, 3, 2, 28}; // Pinos das colunas
uint rows[4] = {8, 7, 6, 5};     // Pinos das linhas

// Mapeamento do teclado
char KEY_MAP[16] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'
};

// Variáveis auxiliares para o teclado
uint _columns[4];
uint _rows[4];
char _matrix_values[16];
uint all_columns_mask = 0x0;
uint column_mask[4];

// Inicializa o teclado matricial
void pico_keypad_init(uint columns[4], uint rows[4], char matrix_values[16]) {
    for (int i = 0; i < 16; i++) {
        _matrix_values[i] = matrix_values[i];
    }

    for (int i = 0; i < 4; i++) {
        _columns[i] = columns[i];
        _rows[i] = rows[i];

        gpio_init(_columns[i]);
        gpio_init(_rows[i]);

        gpio_set_dir(_columns[i], GPIO_IN);
        gpio_set_dir(_rows[i], GPIO_OUT);

        gpio_put(_rows[i], 1);

        all_columns_mask = all_columns_mask + (1 << _columns[i]);
        column_mask[i] = 1 << _columns[i];
    }
}

// Lê o botão pressionado no teclado
char pico_keypad_get_key(void) {
    int row;
    uint32_t cols;

    // Lê as colunas
    cols = gpio_get_all();
    cols = cols & all_columns_mask;

    if (cols == 0x0) {
        return 0; // Nenhum botão pressionado
    }

    for (int j = 0; j < 4; j++) {
        gpio_put(_rows[j], 0);
    }

    for (row = 0; row < 4; row++) {
        gpio_put(_rows[row], 1);

        busy_wait_us(10000);

        cols = gpio_get_all();
        gpio_put(_rows[row], 0);
        cols = cols & all_columns_mask;

        if (cols != 0x0) {
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        gpio_put(_rows[i], 1);
    }

    if (cols == column_mask[0]) {
        return _matrix_values[row * 4 + 0];
    } else if (cols == column_mask[1]) {
        return _matrix_values[row * 4 + 1];
    } else if (cols == column_mask[2]) {
        return _matrix_values[row * 4 + 2];
    } else if (cols == column_mask[3]) {
        return _matrix_values[row * 4 + 3];
    } else {
        return 0;
    }
}

void init_buzzer_pwm() {
    // Configurar o pino como saída de PWM
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    // Configurar o PWM com frequência desejada
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv(&cfg, clock_get_hz(clk_sys) / (BUZZER_FREQ_HZ * HIGH)); // Divisor de clock
    pwm_init(slice_num, &cfg, true);
    // Iniciar o PWM no nível baixo
    pwm_set_gpio_level(BUZZER_PIN, LOW);
}

// Inicializa LEDs e buzzer
void init_peripherals() {
    gpio_init(LED_RED_PIN);
    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_GREEN_PIN);
    init_buzzer_pwm(BUZZER_PIN);// Inicializar o PWM no pino do buzzer

    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_BLUE_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);
}

// Função principal
int main() {
    stdio_init_all();
    pico_keypad_init(columns, rows, KEY_MAP);
    init_peripherals();

    while (true) {
        char key = pico_keypad_get_key();

        // Controle baseado em teclas específicas
        if (key == 'A') {
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_BLUE_PIN, 0);
            gpio_put(LED_GREEN_PIN, 0);
        } else if (key == 'B') {
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_BLUE_PIN, 1);
            gpio_put(LED_GREEN_PIN, 0);
        } else if (key == 'C') {
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_BLUE_PIN, 0);
            gpio_put(LED_GREEN_PIN, 1);
        } else if (key == 'D') {
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_BLUE_PIN, 1);
            gpio_put(LED_GREEN_PIN, 1);
        } else if (key == '#') {
            pwm_set_gpio_level(BUZZER_PIN, HIGH);
        } else {
            // Desliga tudo se nenhuma tecla esperada for pressionada
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_BLUE_PIN, 0);
            gpio_put(LED_GREEN_PIN, 0);
            pwm_set_gpio_level(BUZZER_PIN, LOW);
        }
        busy_wait_us(70000); // Pequeno delay para debounce
    }
}
