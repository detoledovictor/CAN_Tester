# CAN Bus I/O Node

Dois firmwares Arduino para transmissão e recepção de entradas digitais e analógicas via CAN (MCP2515, 500 kbps, 16 MHz).

## Hardware

- Arduino Nano + módulo MCP2515
- AREF externo: 3,0 V | Divisor resistivo: 39 kΩ / 15 kΩ
- CS → pino 10 | INT → pino 2

## Protocolo CAN

| ID      | Conteúdo               |
|---------|------------------------|
| `0x100` | D0–D6 (0 ou 1)         |
| `0x101` | D7–D8 (0 ou 1)         |
| `0x200` | A0–A3 em mV (uint16_t) |
| `0x201` | A4–A7 em mV (uint16_t) |

## Funcionamento

- **Transmissor** — lê 9 digitais e 8 analógicas, envia os 4 frames a cada 1 s.
- **Receptor** — recebe os frames e imprime os valores no Serial Monitor. Detecta desconexão após 3 s sem mensagens.

## Dependência

Biblioteca [`mcp_can`](https://github.com/coryjfowler/MCP_CAN_lib)