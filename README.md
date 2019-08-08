# OpenCV 快速训练模板

## 操作说明

1. 进入 `tools` 目录，编译 `tools` 工具
```shell
cd tools
mkdir build
cd build
cmake ..
make -j2
```

2. 开始训练
```shell
sh train.sh 样本目录 训练目录
```

样本目录为需要训练的数据目录，目录需要：`posdata` 正样本数据；`negdata` 负样本数据。

训练目录为训练数据输出目录，默认为 `train` 目录；可以自己指定。

