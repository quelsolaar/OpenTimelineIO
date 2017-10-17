#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "OpenTimelineIO.h"

class otio
{
	public :	
	void *handle;
	otio()
	{
		handle = NULL;
	}
	otio(char *string)
	{
		handle = otio_load(string);
	}
	otio(OTIOObjectType type, char *name)
	{
		handle = otio_object_create(type, name);
	}
	otio(otio object, bool recursively)
	{
		handle = otio_object_clone(object.handle, (uint)recursively);
	}
	~otio()
	{
		if(otio_object_parent_get(handle) == NULL);
			otio_object_free(handle);
	}
	int save(char *path)
	{
		return otio_save(path, handle);
	}
	OTIOObjectType type()
	{
		return otio_object_type_get(handle);
	}
	char *name_get()
	{
		return otio_object_name_get(handle);
	}
	void name_set(char *name)
	{
		otio_object_name_set(handle, name);
	}
	otio parent()
	{
		otio o;
		o.handle = otio_object_parent_get(handle);
		return o;
	}
	otio next()
	{
		otio o;
		o.handle = otio_object_next_get(handle);
		return o;
	}
	otio previous()
	{
		otio o;
		o.handle = otio_object_previous_get(handle);
		return o;
	}
	void detach()
	{
		otio_object_detach(handle);
	}
	void insert_before(otio object, otio before_object)
	{
		otio_object_insert_before(handle, object.handle, before_object.handle);
	}
	void insert_before(otio object)
	{
		otio_object_insert_before(handle, object.handle, NULL);
	}
	void insert_after(otio object, otio before_object)
	{
		otio_object_insert_after(handle, object.handle, before_object.handle);
	}
	void insert_after(otio object)
	{
		otio_object_insert_after(handle, object.handle, NULL);
	}
	void user_pointer_set(void *pointer)
	{
		otio_object_user_data_set(handle, pointer);
	}
	void *user_pointer_get()
	{
		return otio_object_user_data_get(handle);
	}
	OTIOTime global_start_time()
	{
		return otio_time_object_start_get(handle);
	}
	OTIOTime global_end_time()
	{
		return otio_time_object_start_get(handle);
	}
	uint children_count()
	{
		return otio_composable_children_count(handle);
	}
	otio children_get(uint id)
	{
		otio o;
		o.handle = otio_composable_children_get(handle, id);
		return o;
	}
	uint marker_count()
	{
		return otio_composable_marker_count(handle);
	}
	otio marker_get(uint id)
	{
		otio o;
		o.handle = otio_composable_marker_get(handle, id);
		return o;
	}
	uint effect_count()
	{
		return otio_composable_effect_count(handle);
	}
	otio effect_get(uint id)
	{
		otio o;
		o.handle = otio_composable_effect_get(handle, id);
		return o;
	}
	OTIOTime start_time_get()
	{
		return otio_composable_start_time_get(handle);
	}
	void start_time_set(OTIOTime start_time)
	{
		otio_composable_start_time_set(handle, start_time);
	}
	OTIOTime duration_time_get()
	{
		return otio_composable_duration_time_get(handle);
	}
	void duration_time_set(OTIOTime duration)
	{
		otio_composable_duration_time_set(handle, duration);
	}
	char *reference_kind_get()
	{
		return otio_media_reference_kind_get(handle);
	}
	void reference_kind_set(char *kind)
	{
		otio_media_reference_kind_set(handle, kind);
	}
	char *media_reference_uri_get()
	{
		return otio_media_reference_uri_get(handle);
	}
	void media_reference_uri_set(char *uri)
	{
		otio_media_reference_uri_set(handle, uri);
	}
	OTIOTime media_reference_available_range_get()
	{
		return otio_media_reference_available_range_get(handle);
	}
	void media_reference_available_range_set(OTIOTime available_range)
	{
		otio_media_reference_available_range_set(handle, available_range);
	}
	char *transition_type_get()
	{
		return otio_transition_type_get(handle);
	}
	void transition_type_set(char *type)
	{
		otio_transition_type_set(handle, type);
	}
	OTIOTime transition_in_time_get()
	{
		return otio_transition_in_time_get(handle);
	}
	void transition_in_time_set(OTIOTime in_time)
	{
		otio_transition_in_time_set(handle, in_time);
	}
	OTIOTime transition_out_time_get()
	{
		return otio_transition_out_time_get(handle);
	}
	void transition_out_time_set(OTIOTime out_time)
	{
		otio_transition_out_time_set(handle, out_time);
	}
	OTIOTime marker_time_get()
	{
		return otio_marker_time_get(handle);
	}
	void transition_marker_time_set(OTIOTime time)
	{
		otio_marker_time_set(handle, time);
	}
	char *marker_message_get()
	{
		return otio_marker_message_get(handle);
	}
	void marker_message_set(char *message)
	{
		otio_marker_message_set(handle, message);
	}
};

