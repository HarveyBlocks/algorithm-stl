//
// Created by Lenovo on 2025/12/4.
//

#ifndef ALGORITHM_BYTES_OBJECT_H
#define ALGORITHM_BYTES_OBJECT_H

#include <vector>
#include <string>
#include "../util/type.h"
#include "MetaField.h"


class BytesField {
private:
    int32 length;
    int8 *data;// 数组
public:
    BytesField(int32 length, const int8 *data) : length(length), data(new int8[length]) {
        for (int i = 0; i < length; ++i) this->data[i] = data[i];
    }

    // 深拷贝
    BytesField(const BytesField &src) : BytesField(src.length, src.data) {}

    virtual ~BytesField() {
        delete[] data;
    }
};

// 1. 能根据
class BytesObject {
    std::vector<BytesField> fields;
};

class IMetaType;

class ByteReader {
    virtual void read(IMetaType metaType, BytesField &bytesField) = 0;
};

class ByteWriter {
    virtual void write(IMetaType metaType, BytesField &bytesField) = 0;
};

class MetaFiled {
private:
    IMetaType *type;
    std::string identifier;
public:
    virtual BytesField decode(ByteReader &byteReader) = 0;

    virtual ByteWriter &encode(ByteWriter &byteWriter, const BytesField &bytesField) = 0;
};

class MetaObject {
private:
    std::string identifier;
    std::vector<MetaFiled> fields;
public:
    virtual BytesObject decode(ByteReader &byteReader) = 0;

    virtual ByteWriter &encode(ByteWriter &byteWriter, const BytesObject &bytesField) = 0;
};

// 1. 类型
// 2. 偏移量
class IMetaType {
    /**
     * @return 消耗的byte长度
     */
    virtual int getByteCosts() = 0;

    /**
     * @return 允许消耗消耗的byte长度改变, 则byteCosts为变长
     */
    virtual bool allowByteCostsChange() = 0;
};



#endif //ALGORITHM_BYTES_OBJECT_H
