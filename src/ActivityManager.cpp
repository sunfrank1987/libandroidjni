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

#include "ActivityManager.h"

#include "JNIBase.h"
#include "jutils-details.hpp"

using namespace jni;

CJNIActivityManager::MemoryInfo::MemoryInfo()
 : CJNIBase("android/app/ActivityManager$MemoryInfo")
{
  m_object = new_object(GetClassName(), "<init>", "()V");
  m_object.setGlobal();
}

long CJNIActivityManager::MemoryInfo::availMem() const
{
  return get_field<jlong>(m_object, "availMem");
}

long CJNIActivityManager::MemoryInfo::totalMem() const
{
  return get_field<jlong>(m_object, "totalMem");
}

/***********/

void CJNIActivityManager::getMemoryInfo(MemoryInfo& info) const
{
  call_method<void>(m_object, "getMemoryInfo", "(Landroid/app/ActivityManager$MemoryInfo;)V", info.get_raw());
}
