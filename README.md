# OpenCV 快速训练模板

## 操作说明

1. 进入 `tools` 目录，编译 `tools` 工具

``` shell
cd tools
mkdir build
cd build
cmake ..
make -j2
```

2. 回到根目录，创建正负样本文件夹

``` shell
# negdata 负样本位置
# posdata 正样本位置
mkdir negdata posdata
```

3. 创建保存分类器模型位置
```shell
mkdir xml
```

4. 开始训练
``` shell
sh train.sh
```

