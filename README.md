# Projeto: Teclado Matricial com Raspberry Pi Pico

## Descrição

Este projeto implementa o uso de um teclado matricial 4x4 em conjunto com um Raspberry Pi Pico para controle de LEDs e um buzzer. Cada tecla do teclado matricial executa uma função específica no sistema, permitindo interações diversas com os periféricos conectados.

---

## Funcionalidades

- **Controle de LEDs:**
  - LED vermelho, azul e verde.
  - Ligação e desligamento simultâneo de todos os LEDs.
- **Controle do buzzer:**
  - Emissão de som utilizando PWM.
- **Leitura do teclado matricial:**
  - Mapeamento e identificação precisa de teclas pressionadas.

---

## Requisitos

- Raspberry Pi Pico
- Teclado matricial 4x4
- LEDs (vermelho, azul e verde)
- Buzzer
- Resistores para os LEDs
- Conexões elétricas (jumpers e protoboard)

---

## Funcionamento

### Teclas e suas funções

| Tecla | Função                                                                 |
|-------|------------------------------------------------------------------------|
| **1-9** | Não possui função definida.                                           |
| **A**   | Liga o LED vermelho e desliga os outros LEDs.                        |
| **B**   | Liga o LED azul e desliga os outros LEDs.                            |
| **C**   | Liga o LED verde e desliga os outros LEDs.                           |
| **D**   | Liga todos os LEDs simultaneamente.                                  |
| **#**   | Ativa o buzzer.                                                      |
| **\***  | Desativa todos os LEDs e o buzzer.                                   |

---

## Uso do Wokwi no VSCode para Emulação

O Wokwi é uma ferramenta que permite emular circuitos diretamente no navegador. Para integrar o Wokwi ao VSCode e emular este projeto, siga os passos abaixo:

1. **Instalação do Wokwi:**
   - Acesse o site [Wokwi](https://wokwi.com/) e crie uma conta, se necessário.

2. **Configuração do Projeto:**
   - No Wokwi, monte o circuito com base nos requisitos descritos.
   - Adicione o Raspberry Pi Pico, teclado matricial, LEDs e buzzer ao circuito.
   - Configure os pinos no Wokwi para corresponder aos pinos definidos no código.

3. **Integração com VSCode:**
   - Instale a extensão do Wokwi no VSCode.
   - Abra o projeto no VSCode e utilize a extensão para testar o código diretamente no ambiente do Wokwi.

4. **Execução:**
   - Suba o código no emulador e visualize as interações do teclado com os LEDs e o buzzer diretamente no navegador.

---

## Estrutura de Arquivos

- `teclado_matricial.c`: Código-fonte principal do projeto.
- `CMakeLists.txt`: Configurações do CMake para compilar o projeto.

---

## Compilação e Execução

1. Certifique-se de que o SDK do Raspberry Pi Pico está configurado no seu ambiente.
2. Compile o projeto utilizando `CMake` e `ninja`:
   ```sh
   mkdir build
   cd build
   cmake -G "Ninja" ..
   ninja
   ```
3. Carregue o arquivo `.uf2` gerado no Raspberry Pi Pico.

---

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE). Sinta-se à vontade para usar e modificar conforme necessário.

---

## Autor

Projeto desenvolvido por Iago Virgílio Lopes Macedo de Oliveira.

---

## Observações

Para dúvidas ou sugestões, entre em contato pelo e-mail `iagovirgilio@gmail.com`. Obrigado por usar este projeto!
