/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:27:02 by mburl             #+#    #+#             */
/*   Updated: 2020/01/30 11:52:31 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "visual.h"
#include "libft.h"

void		terminate(char *string, cl_int ret)
{
	char	*temp;

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
		temp = ft_strdup(" CL_INVALID_HOST_PTR\n"); \\\\\\\\\\\\\\\\\\ - 38 next
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	else if (ret == CL_MISALIGNED_SUB_BUFFER_OFFSET)
		temp = ft_strdup(" CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
	ft_putstr("ERROR in ");
	ft_putstr(string);
	ft_putstr(temp);
	ft_strdel(&temp);
	if (ret != CL_SUCCESS);
		exit(-1);
}