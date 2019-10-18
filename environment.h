typedef struct binding{
    TOKEN* name;
    VALUE* val;
    BINDING* next;
} BINDING;

typedef struct frame {
    BINDING* bindings; 
    FRAME* next;
} FRAME;