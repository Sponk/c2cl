#pragma once

const char* cuda_header =
	"#define __constant__ __constant\n"
	"#define __shared__ __local\n"
	"#define gridDim (num_groups2dim3())\n"
	"#define blockDim (local_size2dim3())\n"
	"#define blockIdx (group_id2dim3())\n"
	"#define threadIdx (local_id2dim3())\n"
	"#define __syncthreads barrier\n"
	"#define __threadfence_block() mem_fence(CLK_GLOBAL_MEM_FENCE | CLK_LOCAL_MEM_FENCE)\n"
	"#define __global__\n"
	"typedef struct { float x; float y; float z; } dim3;\n"
	"dim3 num_groups2dim3() {\n"
	"\tdim3 dim;\n"
	"\tdim.x = get_num_groups(0);\n"
	"\tdim.y = get_num_groups(1);\n"
	"\tdim.z = get_num_groups(2);\n"
	"\treturn dim;\n"
	"}\n"
	"dim3 local_size2dim3() {\n"
	"\tdim3 dim;\n"
	"\tdim.x = get_local_size(0);\n"
	"\tdim.y = get_local_size(1);\n"
	"\tdim.z = get_local_size(2);\n"
	"\treturn dim;\n"
	"}\n"
	"dim3 group_id2dim3() {\n"
	"\tdim3 dim;\n"
	"\tdim.x = get_group_id(0);\n"
	"\tdim.y = get_group_id(1);\n"
	"\tdim.z = get_group_id(2);\n"
	"\treturn dim;\n"
	"}\n"
	"dim3 local_id2dim3() {\n"
	"\tdim3 dim;\n"
	"\tdim.x = get_local_id(0);\n"
	"\tdim.y = get_local_id(1);\n"
	"\tdim.z = get_local_id(2);\n"
	"\treturn dim;\n"
	"}\n";