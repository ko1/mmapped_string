#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <ruby/ruby.h>

struct mmap_data {
    int opened;
    int fd;
    size_t length;
    void *addr;
};

static void
mmap_data_free(void *p)
{
    struct mmap_data *data = (struct mmap_data *)p;
    if (munmap(data->addr, data->length) == -1) rb_sys_fail("munmap");
    if (close(data->fd) == -1) rb_sys_fail("close");
    ruby_xfree(data);
}

static size_t
mmap_data_size(const void *p)
{
    return sizeof(struct mmap_data);
}

static const rb_data_type_t mmap_data_type = {
    "mmap_data",
    {NULL, mmap_data_free, mmap_data_size,},
    0, 0, RUBY_TYPED_WB_PROTECTED | RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE
mmap_open(VALUE self, VALUE fname, VALUE lengthv)
{
    struct mmap_data *data;
    VALUE data_val, str;
    data_val = TypedData_Make_Struct(0, struct mmap_data, &mmap_data_type, data);

    data->length = NUM2SIZET(lengthv);
    data->fd = open(StringValueCStr(fname), O_RDONLY);
    if (data->fd == -1) rb_sys_fail("open");

    data->addr = mmap(NULL, data->length, PROT_READ, MAP_PRIVATE, data->fd, 0);
    if (data->addr == MAP_FAILED) rb_sys_fail("mmap");

    if (madvise(data->addr, data->length, MADV_RANDOM) == -1) rb_sys_fail("madvise");

    data->opened = 1;

    str = rb_str_new_static(data->addr, data->length);
    rb_ivar_set(str, rb_intern("mmap_data"), data_val);

    return rb_obj_freeze(str);
}

void
Init_mmapped_string(void)
{
    VALUE mod = rb_define_module("MmappedString");
    rb_define_singleton_method(mod, "mmap_open", mmap_open, 2);
}
