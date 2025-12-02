/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/8/29
 *
 */
#include "Data.h"


void Data::updateData(Array<Byte> *newData) {
    delete this->byteArray;
    this->byteArray = newData;
}


Data::Data(int size) : byteArray(new Array<Byte>(size)) {}

Data::Data(int size, const Byte &initValue) : byteArray(new Array<Byte>(size, initValue)) {}

Data::Data(const Data &obj) : byteArray(nullptr) {
    obj.clone(*this);
}

Data &Data::clone(Data &target) const {
    auto *newData = new Array<Byte>(this->byteArray->getSize());
    Array<Byte>::copy(this->byteArray, newData);
    target.updateData(newData);
    return target;
}

Data &Data::byteCopy(int start, int end, Data &target, int targetStart, int targetEnd) const {
    return Data::byteCopy(*this, start, end, target, targetStart, targetEnd);
}

Data &Data::byteCopy(const Data &source, int start, int end, Data &target, int targetStart, int targetEnd) {
    for (int i = start, j = targetStart; i < end && j < targetEnd; ++i, ++j) {
        target.setByte(j, source.getByte(i));
    }
    return target;
}

Data &Data::bitCopy(int start, int end, Data &target, int targetStart, int targetEnd) const {
    for (int i = start, j = targetStart; i < end && j < targetEnd; ++i, ++j) {
        target.setBit(j, this->getBit(i));
    }
    return target;
}

Data::~Data() {
    delete this->byteArray;
}

int Data::bitCount() const {
    return this->byteCount() * Byte::BIT_COUNT;
}

int Data::byteCount() const {
    return this->byteArray->getSize();
}

Byte &Data::getByte(int index) const {
    return this->byteArray->at(Data::fixIndex(byteCount(), index));
}

Data &Data::setByte(int index, const Byte &value) {
    this->byteArray->set(Data::fixIndex(byteCount(), index), value);
    return *this;
}


Data &Data::setByte(int start, int end, const Byte &value) {
    for (int i = start; i < end; ++i) {
        this->setByte(i, value);
    }
    return *this;
}

Data &Data::setBit0(int start, int end) {
    return this->setBit(start, end, packaging::Bit::ZERO);
}

Data &Data::setBit1(int start, int end) {
    return this->setBit(start, end, packaging::Bit::ONE);
}

Data &Data::setBit(int start, int end, const packaging::Bit &value) {
    for (int i = start; i < end; ++i) {
        this->setBit(i, value);
    }
    return *this;
}

Data &Data::setBit0(int index) {
    return this->setBit(index, packaging::Bit::ZERO);
}

Data &Data::setBit1(int index) {
    return this->setBit(index, packaging::Bit::ONE);
}

Data &Data::setBit(int index, packaging::Bit value) {
    index = fixIndex(this->bitCount(), index);
    this->getByte(index / Byte::BIT_COUNT)
            .selfSet(index % Byte::BIT_COUNT, value);
    return *this;
}

packaging::Bit Data::getBit(int index) const {
    index = fixIndex(this->bitCount(), index);
    return this->getByte(index / Byte::BIT_COUNT)
            .getBit(index % Byte::BIT_COUNT);
}

int Data::fixIndex(int size, int index) {
    return index >= 0 ? index : size + index;
}


Data Data::createLargerData(const Data &data1, const Data &data2) {
    return createLargerData(data1.byteCount(), data2.byteCount());
}

Data Data::createLargerData(int data1Size, int data2Size) {
    return Data(data1Size > data2Size ? data1Size : data2Size);
}


Data Data::grow(int targetByteCount) const {
    int count = this->byteCount();
    Data target = Data::createLargerData(targetByteCount, count);
    for (int i = -1; i >= -count; --i) {
        target.setByte(i, this->getByte(i));
    }
    // this.copyByte(-count,0,target,-count,0);
    return target;
}

int Data::firstTargetNotByte(const packaging::Bit &targetFillBit) const {
    int count = this->byteCount();
    const Byte &targetByte = targetFillBit == packaging::Bit::ONE ? BYTE_FULL : BYTE_NULL;
    for (int i = 0; i < count; ++i) {
        if (this->getByte(i) != targetByte) {
            return i;
        }
    }
    return -1;
}

int Data::firstBit(const packaging::Bit &targetBit) const {
    int byteIndex = firstTargetNotByte(!targetBit);
    if (byteIndex < 0) {
        return -1;
    }
    const Byte &byte = this->getByte(byteIndex);
    int bit = byte.first(targetBit);
    return byteIndex * Byte::BIT_COUNT + bit;
}

bool Data::isZero() const {
    return this->firstTargetNotByte(packaging::Bit::ZERO) == -1;
}

Data Data::insert(int index, const Byte &value) const {
    Data newData(this->byteCount() + 1);
    // pre index
    for (int i = 0; i < index; ++i) {
        newData.setByte(i, this->getByte(i));
    }
    // this.copyByte(0,index,target,0,index);
    // index
    newData.setByte(index, value);
    // post index
    for (int i = index; i < this->byteCount(); ++i) {
        newData.setByte(i + 1, this->getByte(i));
    }
    // this.copyByte(index,this->byteCount(),target,index+1,this->byteCount()+1);
    return newData;
}


Data Data::bitOperator(const Data &other, const BiFunction<const Byte &, const Byte &, Byte> &eachByteFunc) const {
    int thisCount = this->byteCount();
    int otherCount = other.byteCount();
    int shorterCount;
    bool otherIsLonger;
    if ((otherIsLonger = (thisCount < otherCount))) {
        shorterCount = thisCount;
    } else {
        shorterCount = otherCount;
    }
    Data result = Data::createLargerData(*this, other);
    int count = result.byteCount();
    for (int i = -1; i >= -shorterCount; --i) {
        result.setByte(i, eachByteFunc(this->getByte(i), other.getByte(i)));
    }
    // this->data.copyByte(-count,0,result,-count,0,funcObject())
    for (int i = -shorterCount - 1; i >= -count; --i) {
        // remain 剩下的
        const Byte &remainValues = otherIsLonger ? other.getByte(i) : this->getByte(i);
        result.setByte(i, eachByteFunc(remainValues, BYTE_ZERO));
    }
    // this->data.copyByte(-count,-shorterCount,result,-count,-shorterCount,funcObject())
    return result;
}

Data &Data::operator=(const Data &other) {
    if (this != &other) {
        other.clone(*this);
    }
    return *this;

}

Data Data::operator&(const Data &other) const {
    return this->bitOperator(other, [](const Byte &value1, const Byte &value2) {
        return Byte(value1 & value2);
    });
}

Data Data::operator|(const Data &other) const {
    return this->bitOperator(other, [](const Byte &value1, const Byte &value2) {
        return Byte(value1 | value2);
    });
}

Data Data::operator^(const Data &other) const {
    return this->bitOperator(other, [](const Byte &value1, const Byte &value2) {
        return Byte(value1 ^ value2);
    });
}


Data &Data::operator&=(const Data &other) {
    return this->operator=(this->operator&(other));
}

Data &Data::operator|=(const Data &other) {
    return this->operator=(this->operator|(other));
}

Data &Data::operator^=(const Data &other) {
    return this->operator=(this->operator^(other));
}

Data Data::operator~() const {
    int count = this->byteCount();
    Data result(count);
    for (int i = 0; i < count; ++i) {
        result.setByte(i, ~this->getByte(i));
    }
    // this->data.copyByte(0,count,result,0,count,funcObject())
    return result;
}


int Data::compare(const Data &self, const Data &other) {
    int thisCount = self.byteCount();
    int otherCount = other.byteCount();
    int shorterCount;
    int longerCount;
    bool otherIsLonger;
    if ((otherIsLonger = (thisCount < otherCount))) {
        shorterCount = thisCount;
        longerCount = otherCount;
    } else {
        shorterCount = otherCount;
        longerCount = thisCount;
    }
    for (int i = -1; i >= -shorterCount; i--) {
        const Byte &selfByte = self.getByte(i);
        const Byte &otherByte = other.getByte(i);
        if (selfByte > otherByte) {
            return 1;
        } else if (selfByte < otherByte) {
            return -1;
        }
    }
    if (thisCount == otherCount) {
        return 0;
    }
    for (int i = -shorterCount - 1; i >= -longerCount; --i) {
        const Byte &remainValues = otherIsLonger ? other.getByte(i) : self.getByte(i);
        if (remainValues.operator>(0)) {
            return otherIsLonger ? -1 : 1;
        } else if (remainValues.operator<(0)) {
            return otherIsLonger ? 1 : -1;
        }
    }
    return 0;
}

int Data::compareTo(const Data &o) const {
    return Data::compare(*this, o);
}

bool Data::operator==(const Data &o) const {
    return this->compareTo(o) == 0;
}

bool Data::operator!=(const Data &o) const {
    return this->compareTo(o) != 0;
}

bool Data::operator>=(const Data &o) const {
    return this->compareTo(o) >= 0;
}

bool Data::operator<=(const Data &o) const {
    return this->compareTo(o) <= 0;
}

bool Data::operator>(const Data &o) const {
    return this->compareTo(o) < 0;
}

bool Data::operator<(const Data &o) const {
    return this->compareTo(o) < 0;
}

Data Data::operator<<(int offset) const {
    if (offset < 0) {
        return this->operator>>(-offset);
    }
    if (offset == 0) {
        return *this;
    }
    int thisBitCount = this->bitCount();
    Data result(this->byteCount());
    this->bitCopy(offset, thisBitCount, result, 0, thisBitCount);
    return result;
}

Data Data::operator>>(int offset) const {
    if (offset < 0) {
        return this->operator<<(-offset);
    }
    if (offset == 0) {
        return *this;
    }
    int thisBitCount = this->bitCount();
    Data result(this->byteCount());
    this->bitCopy(0, thisBitCount, result, offset, thisBitCount);
    return result;
}

Data &Data::leftMoveByte(int offset, const Byte &fill) { // NOLINT(*-no-recursion)
    if (offset < 0) {
        return this->rightMoveByte(-offset);
    }
    if (offset == 0) {
        return *this;
    }
    int count = this->byteCount();
    Data result(count);
    for (int i = offset, j = 0; i < count && j < count; ++i, ++j) {
        this->setByte(j, this->getByte(i));
    }
    for (int i = count - offset; i < count; ++i) {
        this->setByte(i, fill);
    }
    return *this;
}

Data &Data::rightMoveByte(int offset, const Byte &fill) { // NOLINT(*-no-recursion)
    if (offset < 0) {
        return this->leftMoveByte(-offset);
    }
    if (offset == 0) {
        return *this;
    }
    int count = this->byteCount();
    Data result(count);
    this->bitCopy(0, count, result, offset, count);
    for (int i = -offset - 1, j = -1; i >= -count && j >= -count; --i, --j) {
        this->setByte(j, this->getByte(i));
    }
    for (int i = 0; i < offset; ++i) {
        this->setByte(i, fill);
    }
    return *this;
}

Data &Data::operator<<=(int offset) {
    return this->operator=(this->operator<<(offset));
}

Data &Data::operator>>=(int offset) {
    return this->operator=(this->operator>>(offset));
}


std::ostream &Data::print(std::ostream &os) const {
    Array<Byte> &array = *(this->byteArray);
    return os << (std::string) array << std::endl;
}

Data::operator std::string() const {
    Array<Byte> &array = *(this->byteArray);
    return (std::string) array;
}

Data::operator math::number() const {
    math::number num = 0;
    int high = this->byteCount();
    if (sizeof(math::number) < high) {
        high = sizeof(math::number);
    }
    for (int i = -high; i <= -1; ++i) {
        num <<= 8;
        num += this->getByte(i).get();
    }
    return num;
}

std::ostream &operator<<(std::ostream &os, const Data &obj) {
    return os << *(obj.byteArray);
}

Data Data::subDataBytes(int start, int end, int step) const {
    Data result((end - start) / step);
    int count = result.byteCount();
    for (int i = start, j = 0; i < end, j < count; i += step, j++) {
        result.setByte(j, this->getByte(i));
    }
    return result;
}











