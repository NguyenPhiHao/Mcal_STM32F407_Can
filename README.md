Can/
│
├── Configuration/  # file sinh từ cấu hình Can_Cfg.h
│   │
|   ├── include/
│   │   ├── Can_Cfg.h
│   │
│   ├── src/
│       ├── Can_PBcfg.c
│    
├── IP/ # Can.h, Can_Types.h, Can_GeneralTypes.h
│   │
|   ├── include/
│   │   ├── Can.h
│   │   ├── Can_Types.h
│   │
│   ├── src/
│       ├── Can.c
│       ├── Can_Irq.c
│    
├── IPC/ # Can_Ipc.h
│   │
|   ├── include/
│   │   ├── Can_Ipc.h
│   │   
│   ├── src/
│       ├── Can_Ipc.c
│    
└── HW/# Giao diện truy cập phần cứng
    ├── Can_Hw.h
    └── STM32F407/
        └── Can_Hw_Stm32F407.h
