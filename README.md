# SQ-fuzz(Yuan)
## How to use
先觀察程式執行有哪些參數，並依照參數撰寫設定檔，使用設定檔來協助模糊測試
## example
用 [libjpeg-turbo](https://github.com/libjpeg-turbo/libjpeg-turbo) 當範例
``` 
./AFL/sqfuzz -i i1 -o o1 -m none -s parameters.xml -- ~/afl-target/libjpeg-turbo/build/cjpeg
```
## 致謝
使用 [SQ-fuzz](https://github.com/fdgkhdkgh/SQ-Fuzz]) 修改，對內部程式做優化。
