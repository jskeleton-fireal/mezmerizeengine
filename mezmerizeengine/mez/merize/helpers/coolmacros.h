#pragma once

//foreach macros. this is just to change fw and bw quickly im NOT a dork

#define foreach_base_fw(vVar,vSize) for (int vVar = 0; vVar < vSize; vVar++)
#define foreach_base_bw(vVar,vSize) for (int vVar = vSize-1; vVar >= 0; vVar--)

#define foreach_vector_fw(vVar,vVector) foreach_base_fw(vVar,vVector.size())
#define foreach_vector_bw(vVar,vVector) foreach_base_bw(vVar,vVector.size())