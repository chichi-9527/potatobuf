# potatobuf
通过xml文件生成c++类(.h和.cc文件)并实现序列化与反序列化      
Generate C++ classes (.h and .cc files) from XML files and implement serialization and deserialization

========================
xml 结构要求
括号中为可用的属性

```
package(name)	- class(name)	- enum(name)	- element(name, id)
				- message(name, type)
```

enum 表示类中的枚举
element 表示枚举中的元素
element.name 表示枚举中元素的名称
element.id 表示枚举中元素的值，第一个元素的值必须为 0 或不指定 id

message 表示类中可序列化的成员变量
message.type 表示成员变量的类型，可指定为 element.name

type 包含 ：
	int8
	int16
	int32
	int64
	uint8
	uint16
	uint32
	uint64
	bool
	float
	double
	string
	


potato_c.exe 使用：

	-i  or  --input_file  <input_file>
	-o  or  --output_path  <output_path>