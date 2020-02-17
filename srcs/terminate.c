/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:27:02 by mburl             #+#    #+#             */
/*   Updated: 2020/02/17 14:58:06 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "visual.h"
#include "libft.h"

void		terminate(char *string, cl_int ret)
{
	char	*temp;

	temp = NULL;
	if (ret == CL_SUCCESS)
	{
		ft_putstr(string);
		ft_putstr(" SUCCESS\n");
		return ;
	}
	else if (ret == CL_DEVICE_NOT_FOUND)
		temp = ft_strdup(" CL_DEVICE_NOT_FOUND\n");
	else if (ret == CL_DEVICE_NOT_AVAILABLE)
		temp = ft_strdup(" CL_DEVICE_NOT_AVAILABLE\n");
	else if (ret == CL_COMPILER_NOT_AVAILABLE)
		temp = ft_strdup(" CL_COMPILER_NOT_AVAILABLE\n");
	else if (ret == CL_MEM_OBJECT_ALLOCATION_FAILURE)
		temp = ft_strdup(" CL_MEM_OBJECT_ALLOCATION_FAILURE\n");
	else if (ret == CL_OUT_OF_RESOURCES)
		temp = ft_strdup(" CL_OUT_OF_RESOURCES\n");
	else if (ret == CL_OUT_OF_HOST_MEMORY)
		temp = ft_strdup(" CL_OUT_OF_HOST_MEMORY\n");
	else if (ret == CL_PROFILING_INFO_NOT_AVAILABLE)
		temp = ft_strdup(" CL_PROFILING_INFO_NOT_AVAILABLE\n");
	else if (ret == CL_MEM_COPY_OVERLAP)
		temp = ft_strdup(" CL_MEM_COPY_OVERLAP\n");
	else if (ret == CL_IMAGE_FORMAT_MISMATCH)
		temp = ft_strdup(" CL_IMAGE_FORMAT_MISMATCH\n");
	else if (ret == CL_IMAGE_FORMAT_NOT_SUPPORTED)
		temp = ft_strdup(" CL_IMAGE_FORMAT_NOT_SUPPORTED\n");
	else if (ret == CL_BUILD_PROGRAM_FAILURE)								// LOG FILE
		temp = ft_strdup(" CL_BUILD_PROGRAM_FAILURE\n");
	else if (ret == CL_MAP_FAILURE)
		temp = ft_strdup(" CL_MAP_FAILURE\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST)
		temp = ft_strdup(" CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST\n");
	else if (ret == CL_COMPILE_PROGRAM_FAILURE)
		temp = ft_strdup(" CL_COMPILE_PROGRAM_FAILURE\n");
	else if (ret == CL_LINKER_NOT_AVAILABLE)
		temp = ft_strdup(" CL_LINKER_NOT_AVAILABLE\n");
	else if (ret == CL_LINK_PROGRAM_FAILURE)
		temp = ft_strdup(" CL_LINK_PROGRAM_FAILURE\n");
	else if (ret == CL_DEVICE_PARTITION_FAILED)
		temp = ft_strdup(" CL_DEVICE_PARTITION_FAILED\n");
	else if (ret == CL_KERNEL_ARG_INFO_NOT_AVAILABLE)
		temp = ft_strdup(" CL_KERNEL_ARG_INFO_NOT_AVAILABLE\n");
	else if (ret == CL_INVALID_VALUE)
		temp = ft_strdup(" CL_INVALID_VALUE\n");
	else if (ret == CL_INVALID_DEVICE_TYPE)
		temp = ft_strdup(" CL_INVALID_DEVICE_TYPE\n");
	else if (ret == CL_INVALID_PLATFORM)
		temp = ft_strdup(" CL_INVALID_PLATFORM\n");
	else if (ret == CL_INVALID_DEVICE)
		temp = ft_strdup(" CL_INVALID_DEVICE\n");
	else if (ret == CL_INVALID_CONTEXT)
		temp = ft_strdup(" CL_INVALID_CONTEXT\n");
	else if (ret == CL_INVALID_QUEUE_PROPERTIES)
		temp = ft_strdup(" CL_INVALID_QUEUE_PROPERTIES\n");
	else if (ret == CL_INVALID_COMMAND_QUEUE)
		temp = ft_strdup(" CL_INVALID_COMMAND_QUEUE\n");
	else if (ret == CL_INVALID_HOST_PTR)
		temp = ft_strdup(" CL_INVALID_HOST_PTR\n");
	else if (ret == CL_INVALID_MEM_OBJECT)
		temp = ft_strdup(" CL_INVALID_MEM_OBJECT\n");
	else if (ret == CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
		temp = ft_strdup(" CL_INVALID_IMAGE_FORMAT_DESCRIPTOR\n");
	else if (ret == CL_INVALID_IMAGE_SIZE)
		temp = ft_strdup(" CL_INVALID_IMAGE_SIZE\n");
	else if (ret == CL_INVALID_SAMPLER)
		temp = ft_strdup(" CL_INVALID_SAMPLER\n");
	else if (ret == CL_INVALID_BINARY)
		temp = ft_strdup(" CL_INVALID_BINARY\n");
	else if (ret == CL_INVALID_BUILD_OPTIONS)
		temp = ft_strdup(" CL_INVALID_BUILD_OPTIONS\n");
	else if (ret == CL_INVALID_PROGRAM)
		temp = ft_strdup(" CL_INVALID_PROGRAM\n");
	else if (ret == CL_INVALID_PROGRAM_EXECUTABLE)
		temp = ft_strdup(" CL_INVALID_PROGRAM_EXECUTABLE\n");
	else if (ret == CL_INVALID_KERNEL_NAME)
		temp = ft_strdup(" CL_INVALID_KERNEL_NAME\n");
	else if (ret == CL_INVALID_KERNEL_DEFINITION)
		temp = ft_strdup(" CL_INVALID_KERNEL_DEFINITION\n");
	else if (ret == CL_INVALID_KERNEL)
		temp = ft_strdup(" CL_INVALID_KERNEL\n");
	else if (ret == CL_INVALID_ARG_INDEX)
		temp = ft_strdup(" CL_INVALID_ARG_INDEX\n");
	else if (ret == CL_INVALID_ARG_VALUE)
		temp = ft_strdup(" CL_INVALID_ARG_VALUE\n");
	else if (ret == CL_INVALID_ARG_SIZE)
		temp = ft_strdup(" CL_INVALID_ARG_SIZE\n");
	else if (ret == CL_INVALID_KERNEL_ARGS)
		temp = ft_strdup(" CL_INVALID_KERNEL_ARGS\n");
	else if (ret == CL_INVALID_WORK_DIMENSION)
		temp = ft_strdup(" CL_INVALID_WORK_DIMENSION\n");
	else if (ret == CL_INVALID_WORK_GROUP_SIZE)
		temp = ft_strdup(" CL_INVALID_WORK_GROUP_SIZE\n");
	else if (ret == CL_INVALID_WORK_ITEM_SIZE)
		temp = ft_strdup(" CL_INVALID_WORK_ITEM_SIZE\n");
	else if (ret == CL_INVALID_GLOBAL_OFFSET)
		temp = ft_strdup(" CL_INVALID_GLOBAL_OFFSET\n");
	else if (ret == CL_INVALID_EVENT_WAIT_LIST)
		temp = ft_strdup(" CL_INVALID_EVENT_WAIT_LIST\n");
	else if (ret == CL_INVALID_EVENT)
		temp = ft_strdup(" CL_INVALID_EVENT\n");
	else if (ret == CL_INVALID_OPERATION)
		temp = ft_strdup(" CL_INVALID_OPERATION\n");
	else if (ret == CL_INVALID_GL_OBJECT)
		temp = ft_strdup(" CL_INVALID_GL_OBJECT\n");
	else if (ret == CL_INVALID_BUFFER_SIZE)
		temp = ft_strdup(" CL_INVALID_BUFFER_SIZE\n");
	else if (ret == CL_INVALID_MIP_LEVEL)
		temp = ft_strdup(" CL_INVALID_MIP_LEVEL\n");
	else if (ret == CL_INVALID_GLOBAL_WORK_SIZE)
		temp = ft_strdup(" CL_INVALID_GLOBAL_WORK_SIZE\n");
	else if (ret == CL_INVALID_PROPERTY)
		temp = ft_strdup(" CL_INVALID_PROPERTY\n");
	else if (ret == CL_INVALID_IMAGE_DESCRIPTOR)
		temp = ft_strdup(" CL_INVALID_COMPILER_OPTIONS\n");
	ft_putstr("ERROR in ");
	ft_putstr(string);
	ft_putstr(temp);
	ft_strdel(&temp);
	if (ret != CL_SUCCESS)
		exit(-1);
}