// Returns the used value of a value.

int unpackIntValue(VALUE* value){
  if(value->type == 0){
    return value->v.integer;
  }
  else if(value->type == 1){
    return value->v.boolean;
  }
}

int unpackStrValue(VALUE* value){
  return atoi(value->v.string);
}

// Packs a specific value type into the generalised value

VALUE* packValue(int type, int value){
  VALUE* v = malloc(sizeof(VALUE*));
  
  v->type = type;
  
  if(type == 0){
    v->v.integer = value;
  }
  else if(type == 1){
    v->v.boolean = value;
  }
  else if(type == 2){
    char str[12];
    sprintf(str, "%d", value);
    v->v.string = str;
  }
  
  return v;
}