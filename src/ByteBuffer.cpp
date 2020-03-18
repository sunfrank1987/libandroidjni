/*
 *      Copyright (C) 2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "ByteBuffer.h"
#include "jutils-details.hpp"

using namespace jni;

const char* CJNIByteBuffer::m_classname = "java/nio/ByteBuffer";

CJNIByteBuffer CJNIByteBuffer::CJNIByteBuffer::allocateDirect(int capacity)
{
  return CJNIByteBuffer(call_static_method<jhobject>(m_classname,
    "allocateDirect", "(I)Ljava/nio/ByteBuffer;",
    capacity));
}

CJNIByteBuffer CJNIByteBuffer::allocate(int capacity)
{
  return CJNIByteBuffer(call_static_method<jhobject>(m_classname,
    "allocate", "(I)Ljava/nio/ByteBuffer;",
    capacity));
}

CJNIByteBuffer CJNIByteBuffer::wrap(const std::vector<char> &array, int start, int byteCount)
{
  JNIEnv *env = xbmc_jnienv();
  jsize size  = array.size();
  jbyteArray bytearray = env->NewByteArray(size);
  env->SetByteArrayRegion(bytearray, 0, size, (jbyte*)&array[0]);

  return CJNIByteBuffer(call_static_method<jhobject>(m_classname,
    "wrap","([BII)Ljava/nio/ByteBuffer;",
    bytearray, start, byteCount));
}

CJNIByteBuffer CJNIByteBuffer::wrap(const std::vector<char> &array)
{
  JNIEnv *env = xbmc_jnienv();
  jsize size  = array.size();
  jbyteArray bytearray = env->NewByteArray(size);
  env->SetByteArrayRegion(bytearray, 0, size, (jbyte*)&array[0]);

  return CJNIByteBuffer(call_static_method<jhobject>(m_classname,
    "wrap","([B)Ljava/nio/ByteBuffer;",
                                                     bytearray));
}

CJNIByteBuffer CJNIByteBuffer::wrap(const jharray &array)
{
  return CJNIByteBuffer(call_static_method<jhobject>(m_classname,
    "wrap","([B)Ljava/nio/ByteBuffer;", array));
}

CJNIByteBuffer CJNIByteBuffer::duplicate()
{
  return CJNIByteBuffer(call_method<jhobject>(m_object,
    "duplicate","()Ljava/nio/ByteBuffer;"));
}

CJNIByteBuffer CJNIByteBuffer::get(const std::vector<char> &dst, int dstOffset, int byteCount)
{
  JNIEnv *env = xbmc_jnienv();
  jsize size  = dst.size();
  jbyteArray bytearray = env->NewByteArray(size);
  env->SetByteArrayRegion(bytearray, 0, size, (jbyte*)&dst[0]);

  return CJNIByteBuffer(call_method<jhobject>(m_object,
    "get","([BII)Ljava/nio/ByteBuffer;",
    bytearray, dstOffset, byteCount));
}

CJNIByteBuffer CJNIByteBuffer::get(const std::vector<char> &dst)
{
  JNIEnv *env = xbmc_jnienv();
  jsize size  = dst.size();
  jbyteArray bytearray = env->NewByteArray(size);
  env->SetByteArrayRegion(bytearray, 0, size, (jbyte*)&dst[0]);

  return CJNIByteBuffer(call_method<jhobject>(m_object,
    "get","([B)Ljava/nio/ByteBuffer;",
    bytearray));
}

CJNIByteBuffer CJNIByteBuffer::put(const CJNIByteBuffer &src)
{
  return CJNIByteBuffer(call_method<jhobject>(m_object,
    "put","(Ljava/nio/ByteBuffer;)Ljava/nio/ByteBuffer;",
    src.get_raw()));
}

CJNIByteBuffer CJNIByteBuffer::put(const std::vector<char> &src, int srcOffset, int byteCount)
{
  JNIEnv *env = xbmc_jnienv();
  jsize size  = src.size();
  jbyteArray bytearray = env->NewByteArray(size);
  env->SetByteArrayRegion(bytearray, 0, size, (jbyte*)src.data());

  return CJNIByteBuffer(call_method<jhobject>(m_object,
    "put","([BII)Ljava/nio/ByteBuffer;",
    bytearray, srcOffset, byteCount));
}

CJNIByteBuffer CJNIByteBuffer::put(const std::vector<char> &src)
{
  JNIEnv *env = xbmc_jnienv();
  jsize size  = src.size();
  jbyteArray bytearray = env->NewByteArray(size);
  env->SetByteArrayRegion(bytearray, 0, size, (jbyte*)src.data());

  return CJNIByteBuffer(call_method<jhobject>(m_object,
    "put","([B)Ljava/nio/ByteBuffer;",
    bytearray));
}

bool CJNIByteBuffer::hasArray()
{
  return call_method<jboolean>(m_object,
    "hasArray", "()Z");
}

std::vector<char> CJNIByteBuffer::array()
{
  JNIEnv *env = xbmc_jnienv();
  jhbyteArray array = call_method<jhbyteArray>(m_object,
    "array", "()[B");

  jsize size = env->GetArrayLength(array.get());

  std::vector<char> result;
  result.resize(size);
  env->GetByteArrayRegion(array.get(), 0, size, (jbyte*)result.data());

  return result;
}

int CJNIByteBuffer::arrayOffset()
{
  return call_method<int>(m_object,
    "arrayOffset", "()I");
}

std::string CJNIByteBuffer::toString()
{
  return jcast<std::string>(call_method<jhstring>(m_object,
    "toString", "()Ljava/lang/String;"));
}

int CJNIByteBuffer::hashCode()
{
  return call_method<int>(m_object,
    "hashCode", "()I");
}

/*
bool CJNIByteBuffer::equals(CJNIObject other)
{
}
*/

int CJNIByteBuffer::compareTo(const CJNIByteBuffer &otherBuffer)
{
  return call_method<int>(m_object,
    "compareTo","(Ljava/nio/ByteBuffer;)I",
    otherBuffer.get_raw());
}

/*
CJNIByteOrder CJNIByteBuffer::order()
{
}

CJNIByteBuffer CJNIByteBuffer::order(CJNIByteOrder byteOrder)
{
}

CJNIObject CJNIByteBuffer::array()
{
}

int CJNIByteBuffer::compareTo(const CJNIObject &otherBuffer)
{
}
*/
/**
 * 
 * from : https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/functions.html#NewDirectByteBuffer
 *
 * NewDirectByteBuffer
 * jobject NewDirectByteBuffer(JNIEnv* env, void* address, jlong capacity);
 * 
 * Allocates and returns a direct java.nio.ByteBuffer referring to the block of memory 
 * starting at the memory address address and extending capacity bytes.
 * 
 * Native code that calls this function and returns the resulting byte-buffer object to Java-level 
 * code should ensure that the buffer refers to a valid region of memory that is accessible for reading and, 
 * if appropriate, writing. An attempt to access an invalid memory location from Java code will either 
 * return an arbitrary value, have no visible effect, or cause an unspecified exception to be thrown.
 * 
 * LINKAGE:
 * Index 229 in the JNIEnv interface function table.
 * 
 * PARAMETERS:
 * env: the JNIEnv interface pointer
 * 
 * address: the starting address of the memory region (must not be NULL)
 * 
 * capacity: the size in bytes of the memory region (must be positive)
 * 
 * RETURNS:
 * Returns a local reference to the newly-instantiated java.nio.ByteBuffer object. 
 * Returns NULL if an exception occurs, or if JNI access to direct buffers is not supported by this virtual machine.
 * 
 * EXCEPTIONS:
 * OutOfMemoryError: if allocation of the ByteBuffer object fails
 * 
 * SINCE:
 * JDK/JRE 1.4
 * 
 * ex:
 * memory of address will not release after CJNIByteBuffer destruct.
 * 
 * */
// jobject     (*NewDirectByteBuffer)(JNIEnv*, void*, jlong);
CJNIByteBuffer CJNIByteBuffer::newDirectByteBuffer(void*address, long capacity) {
    JNIEnv *env = xbmc_jnienv();
    return CJNIByteBuffer(jholder<jobject>(env->NewDirectByteBuffer(address, capacity)));
}

/**
 * 
 * from : https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/functions.html#GetDirectBufferAddress
 * 
 * GetDirectBufferAddress
 * void* GetDirectBufferAddress(JNIEnv* env, jobject buf);
 * 
 * Fetches and returns the starting address of the memory region referenced by the given direct java.nio.Buffer.
 * 
 * This function allows native code to access the same memory region that is accessible to Java code via the buffer object.
 * 
 * LINKAGE:
 * Index 230 in the JNIEnv interface function table.
 * 
 * PARAMETERS:
 * env: the JNIEnv interface pointer
 * 
 * buf: a direct java.nio.Buffer object (must not be NULL)
 * 
 * RETURNS:
 * Returns the starting address of the memory region referenced by the buffer. 
 * Returns NULL if the memory region is undefined, if the given object is not a direct java.nio.Buffer, 
 * or if JNI access to direct buffers is not supported by this virtual machine.
 * 
 * SINCE:
 * JDK/JRE 1.4
*/
void* CJNIByteBuffer::getDirectBufferAddress() {
  JNIEnv *env = xbmc_jnienv();
    if(!m_object) {
        return nullptr;
    }
    return env->GetDirectBufferAddress(m_object.get());
}

/**
 * from : https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/functions.html#GetDirectBufferCapacity
 * jlong GetDirectBufferCapacity(JNIEnv* env, jobject buf);
 * 
 * Fetches and returns the capacity of the memory region referenced by the given direct java.nio.Buffer. 
 * The capacity is the number of elements that the memory region contains.
 * 
 * LINKAGE:
 * Index 231 in the JNIEnv interface function table.
 * 
 * PARAMETERS:
 * env: the JNIEnv interface pointer
 * 
 * buf: a direct java.nio.Buffer object (must not be NULL)
 * 
 * RETURNS:
 * Returns the capacity of the memory region associated with the buffer. 
 * Returns -1 if the given object is not a direct java.nio.Buffer, 
 * if the object is an unaligned view buffer and the processor architecture does not support unaligned access, 
 * or if JNI access to direct buffers is not supported by this virtual machine.
 * 
 * SINCE:
 * JDK/JRE 1.4
*/
long CJNIByteBuffer::getDirectBufferCapacity() {
    JNIEnv *env = xbmc_jnienv();
    if(!m_object) {
        return -1;
    }
    return env->GetDirectBufferCapacity(m_object.get());
}

