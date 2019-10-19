typedef struct binding{
    TOKEN* name;
    VALUE* val;
    struct BINDING* next;
} BINDING;

typedef struct frame {
    BINDING* bindings; 
    struct FRAME* next;
} FRAME;

typedef struct ENV {
    FRAME* frames;
} ENV;