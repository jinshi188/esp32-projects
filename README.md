# ESP32 学习项目合集

成都理工大学软件工程 · 嵌入式方向学习记录

## 项目列表

### 1. blink —— 板载 LED 闪烁

最基础的 GPIO 输出实验：让板载 LED 以 500ms 间隔闪烁，并通过串口回传状态。

**硬件**
- 开发板：ESP32-DevKitC（ESP32-WROOM-32）
- 板载 LED：GPIO2

**关键代码**
```cpp
#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
```

**现象**：LED 每 0.5 秒亮灭一次，串口 115200 波特率输出 `LED ON` / `LED OFF`。

**编译烧录**（PlatformIO）
```bash
cd blink
pio run            # 编译
pio run -t upload  # 烧录
pio device monitor # 串口监视器
```

### 2. 项目一 · 呼吸灯 + 按键交互小灯（进行中）

把 blink 升级成能交互的小作品：PWM 无级调光 + 按键切换模式 + 串口日志。
核心是用 `millis()` 取代 `delay()` 做时间调度，让「呼吸渐变 / 按键检测 / 串口输出」互不阻塞。

> 状态：编写中。完成后在此补上接线表、串口输出示例与学到的知识点。

## 开发环境

| 项 | 版本 / 说明 |
|---|---|
| 编辑器 | VS Code + PlatformIO IDE |
| 框架 | Arduino (framework-arduinoespressif32) |
| 平台 | espressif32，board = esp32dev |
| 串口芯片 | CH340 |
| 主机系统 | Windows |

## 目录结构

```
esp32-projects/
└── blink/
    ├── src/main.cpp        # 主程序
    ├── platformio.ini      # PlatformIO 配置
    ├── include/  lib/  test/
    └── .gitignore          # 已排除 .pio 编译产物
```
