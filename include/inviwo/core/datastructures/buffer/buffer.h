/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2013-2015 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#ifndef IVW_BUFFER_H
#define IVW_BUFFER_H

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/datastructures/data.h>

namespace inviwo {

enum BufferType {
    POSITION_ATTRIB,
    NORMAL_ATTRIB,
    COLOR_ATTRIB,
    TEXCOORD_ATTRIB,
    CURVATURE_ATTRIB,
    INDEX_ATTRIB,
    NUMBER_OF_BUFFER_TYPES
};

enum BufferUsage { STATIC, DYNAMIC };

class IVW_CORE_API Buffer : public Data {
public:
    Buffer(size_t size, const DataFormatBase* format = DataFormatBase::get(),
           BufferType type = POSITION_ATTRIB, BufferUsage usage = STATIC);
    Buffer(const Buffer& rhs);
    Buffer& operator=(const Buffer& that);
    virtual Buffer* clone() const;
    virtual ~Buffer();

    void resizeBufferRepresentations(Buffer* targetBuffer, size_t targetSize);

    size_t getSize() const;
    void setSize(size_t size);

    size_t getSizeInBytes();
    BufferType getBufferType() const { return type_; }

    static uvec3 COLOR_CODE;
    static const std::string CLASS_IDENTIFIER;

protected:
    virtual DataRepresentation* createDefaultRepresentation();

private:
    size_t size_;
    BufferType type_;
    BufferUsage usage_;
};

template <typename T, BufferType A = POSITION_ATTRIB>
class BufferPrecision : public Buffer {
public:
    BufferPrecision(size_t size = 0, BufferUsage usage = STATIC)
        : Buffer(size, DataFormat<T>::get(), A, usage) {}
    BufferPrecision(BufferUsage usage) : Buffer(0, DataFormat<T>::get(), A, usage) {}
    BufferPrecision(const BufferPrecision& rhs) : Buffer(rhs) {}
    BufferPrecision& operator=(const BufferPrecision& that) {
        if (this != &that) {
            Buffer::operator=(that);
        }
        return *this;
    }
    virtual BufferPrecision<T, A>* clone() const { return new BufferPrecision<T, A>(*this); }

    virtual ~BufferPrecision() {}

private:
    static const DataFormatBase* defaultformat() { return DataFormat<T>::get(); }
};

typedef BufferPrecision<vec2, POSITION_ATTRIB> Position2dBuffer;
typedef BufferPrecision<vec2, TEXCOORD_ATTRIB> TexCoord2dBuffer;
typedef BufferPrecision<vec3, POSITION_ATTRIB> Position3dBuffer;
typedef BufferPrecision<vec4, COLOR_ATTRIB> ColorBuffer;
typedef BufferPrecision<vec3, NORMAL_ATTRIB> NormalBuffer;
typedef BufferPrecision<vec3, TEXCOORD_ATTRIB> TexCoord3dBuffer;
typedef BufferPrecision<float, CURVATURE_ATTRIB> CurvatureBuffer;
typedef BufferPrecision<std::uint32_t, INDEX_ATTRIB> IndexBuffer;

// Scalar buffers
typedef BufferPrecision<float, POSITION_ATTRIB> FloatBuffer;
typedef BufferPrecision<int, INDEX_ATTRIB> IntBuffer;
typedef BufferPrecision<std::uint32_t, INDEX_ATTRIB> BufferUInt32;
typedef BufferPrecision<double, POSITION_ATTRIB> DoubleBuffer;

// Vector buffers
typedef BufferPrecision<vec2, TEXCOORD_ATTRIB> FloatVec2Buffer;
typedef BufferPrecision<vec3, POSITION_ATTRIB> FloatVec3Buffer;
typedef BufferPrecision<vec4, COLOR_ATTRIB>    FloatVec4Buffer;

typedef BufferPrecision<dvec2, TEXCOORD_ATTRIB> DoubleVec2Buffer;
typedef BufferPrecision<dvec3, POSITION_ATTRIB> DoubleVec3Buffer;
typedef BufferPrecision<dvec4, COLOR_ATTRIB>    DoubleVec4Buffer;

typedef BufferPrecision<ivec2, POSITION_ATTRIB> IntVec2Buffer;
typedef BufferPrecision<ivec3, POSITION_ATTRIB> IntVec3Buffer;
typedef BufferPrecision<ivec4, POSITION_ATTRIB> IntVec4Buffer;

typedef BufferPrecision<uvec2, POSITION_ATTRIB> UIntVec2Buffer;
typedef BufferPrecision<uvec3, POSITION_ATTRIB> UIntVec3Buffer;
typedef BufferPrecision<uvec4, POSITION_ATTRIB> UIntVec4Buffer;

}  // namespace

#endif  // IVW_BUFFER_H
