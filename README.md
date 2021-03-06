# lok-lang

a plan for a "programing language" that compiles to c code.


the purpouse of the language is to modernize the syntax and make it more uniform as well as extend it with a few features that makes the code both more consise and more verbose at the same time.

### Features

 - **function overloading** aswell as operator overloading for structs
 - **namespaces** ability to bundle functionality in namespaces and include where necessary
 - **type parameters** type paramenters for structs aswell as namespaces (syntax has yet to be written)
 - **lambda expressions**

---

# behavior defenitions.

## Types

Syntax:
 ```javascript
var i : u8  = 10;
var j : u16 = 11;
var k : u32 = 12;
var l : u64 = 13;

var m : i8  = -10;
var n : i16 = -11;
var o : i32 = -12;
var p : i64 = -13;

var ch : char  = 'p';

var d : double = 3.1415926535;
var f : float  = 2.71828182845;

var str : *char = "Hello, World!";

var arr : u32[] = {1, 1, 2, 3, 5, 8};

struct complex:
	var re : double;
	var im : double;

struct byteColor:
	union:
		var byterep : u8;
		struct:
			var red   : [3]
			var green : [3]
			var blue  : [2]

var green : byteColor = {.red = b000, .green = b111, .blue = 0}; //c like initialization
 ```

compiler output
```c
unsigned char      i = 10;    //
unsigned short int j = 11;    // added spaces for readability is not a compiler feature
unsigned int       k = 12;    //
unsigned long long l = 13;

signed char      m = -10;
signed short int n = -11;
signed int       o = -12;
signed long long p = -13;

char ch  = 'p';

double d = 3.1415926535;
float  f = 2.71828182845;

char * str = "Hello, World!";

unsigned int arr[] = {1, 1, 2, 3, 5, 8};

struct complex {
	double re;
	double im;
};

struct byteColor {
	union{
		unsigned char byterep;
		struct {
			int red   : 3;
			int green : 3;
			int blue  : 2;
		};
	};
};

struct byteColor green = {.red = b000, .green = b111, .blue = 0};
```

## controll structures

 - **if and ternary**
```javascript

var val1 : i32 = 87;
var val2 : i32 = -7;

// ternary operator
var largest : i32 = (val1 > val2) ? val1 : val2;

//if statements
if (val1 < 0):
	printf("val1 is less than 0");
else if (val2 < val1):
	printf("val2 is less than val1");
else:
	printf("i dont even know");
```
compiled output:
```c

int val1 = 87;
int val2 = -7;

// ternary operator
int largest = (val1 > val2) ? val1 : val2;

//if statements
if (val1 < 0) {
	printf("val1 is less than 0");
}
else if (val2 < val1) {
	printf("val2 is less than val1");
}
else {
	printf("i dont even know");
}
```
---

- **loops**

	```javascript
//while loops
while (7 == 7):
	printf("hello, againt :)\n");

loop:
	printf("hello, againt :)\n");

do (7 == 8):
	printf("hello, only once\n");

//for loops
for (var i : i32 = 0; i < 10; i++):
	printf("printing 0 -> 9 : %i\n", i);

var len : u8 = 6;
var fib : i32[] = {1, 1, 2, 3, 5, 8};

for (i <- 0:len):
	printf("printing fibonachi numbers : %i\n", i);

var str : *char = "Hello, World!";
for(c <- str):
	printf("%c",c);
```
compiled output:

```c
//while loops
while (7 == 7) {
	printf("hello, againt :)\n");
}

for(;;) {
	printf("hello, againt :)\n");
}

do {
	printf("hello, only once\n");
} while (7 == 8);

//for loops
for (int i = 0; i < 10; i++) {
	printf("printing 0 -> 9 : %i\n", i);
}

unsigned char len = 6;
int fib[] = {1, 1, 2, 3, 5, 8};

for (int i = 0; i < len; i++) {
	printf("printing fibonachi numbers : %i\n", i);
}

char * str = "Hello, World!";

for(char * c = str; c != NULL; c++){
	printf("%c",(*c));
}
```

---

- **case matching**
```javascript

var fruit : u32; // matching to made up constants
var summer : u8 = 1;

switch fruit:
	case (BANANA):                    printf("banana");
	case (LEMON)(ORANGE)(GRAPEFRUIT): printf("citrus");
	case (PEAR) && (summer):          printf("pear in the summer");
	case:                             printf("no fruit, or maybe pear");
```

	compiled output
```c

unsigned int fruit; // matching to made up constants
unsigned char summer = 1;

switch (fruit) {
	case BANANA:
		printf("banana");
		break;
	case LEMON:
	case ORANGE:
	case GRAPEFRUIT:
		printf("citrus");
		break;
	case PEAR:
		if (summer){
			printf("pear in the summer");
		}
		break;
	default:
		printf("no fruit, or maybe pear");
		break;
}
```
---

## functions

syntax:
```scala

def sum(a : i32, b : i32) : i32 =
	return a + b;

def sum(a : i32[], len : i32) : i32 =
	var res : i32 = 0;
	for(i <- 0:len):
		res += a[i];
	return res;
```

compiled output:

```c

int sum(int a, int b) {
	return a + b;
}

int sum_overload_a_len_HAGFE(int a[], int len) {
	int res = 0;
	for (int i = 0; i < len; i++) {
		res += a[i]
	}
	return res;
}
```
## New syntax and features

 - **namespaces** <br>
	- **syntax:** <span style="color:rgb(154, 204, 251)">`def`</span><span style="color:rgb(117, 225,231)">`<name>`</span>`:`<span style="color:rgb(99, 197, 253)">`namespace`</span>`[`<span style="color:rgb(224, 124, 142)">`T`</span>`] =`
	- T is the type parameter, if a namespace needs multiple type parameters `[T][G][B]`or `[T, G, B]`<br>
		syntax may be used
 - **struct constructor** <br>
	- **syntax:** <span style="color:rgb(117, 225, 231)">`constructor`</span>`(p1, p2 .. pn)`
	- parameters should be names of struct members, members that are not included in the constructor
	can be given a default initialization value by declaring it with one in the struct.
 - **operator overloading** <br>
	- **syntax:**<span style="color:rgb(154, 204, 251)">`operator`</span><span style="color:rgb(180, 48, 102)">`<rules>`</span><span style="color:rgb(99, 197, 253)">`<operator>`</span>`( p :`<span style="color:rgb(154, 204, 251)">`param`</span>`) : <`<span style="color:rgb(154, 204, 251)">`return type`</span>`> =`
	- **rules** the rules for a operator overloading functions have two functions, to specify whether or not the struct instance it is applied to
		has to be a pointer to an instance or an instance, aswell as the operations comutativity.
		- **syntax:** <span style="color:rgb(216, 142, 79)">`#==>`</span> the first token `#` specifies that the variable must be a instance, not having any token there
		means that it does not matter and a `&` sign means it must be a reference/pointer. <br>
		the second part `==>` specifies the operations comutativity.



| **syntax**   | a + b   | b + a   | &a + b   | b + &a   |
|--------------|:-------:|:-------:|:--------:|---------:|
|              | valid   | valid   | valid    | valid    |
|  <span style="color:rgb(216, 142, 79)">`==>`</span>         | valid   |         | valid    |          |
|  <span style="color:rgb(216, 142, 79)">`<==`</span>         |         | valid   |          | valid    |
|  <span style="color:rgb(216, 142, 79)">`<=>`</span>         | valid   | valid   | valid    | valid    |
| <span style="color:rgb(216, 142, 79)">`#==>`</span>         | valid   |         |          |          |
| <span style="color:rgb(216, 142, 79)">`#<==`</span>        |         | valid   |          |          |
| <span style="color:rgb(216, 142, 79)">`#<=>`</span>         | valid   | valid   |          |          |
| <span style="color:rgb(216, 142, 79)">`&==>`</span>         |         |         | valid    |          |
| <span style="color:rgb(216, 142, 79)">`&<==`</span>         |         |         |          | valid    |
| <span style="color:rgb(216, 142, 79)">`&<=>`</span>         |         |         | valid    | valid    |

 - **Advanced structs and namespaces**

more class like struct functionality<br>
syntax:

```c++
/**
 *   advanced struct with a type parameter 'T'.
 *
 *   'constructor()' contains the names inside the struct
 *   that cunstruction sould initialize
 *
 *   'operator' specifiec operator overloading defenition.
 *   '==>' '<=>' '<==' comutativity specifiers defines
 *   if both a + b and b + a should work, only available
 *   when input isnt of the struct type
	 *
 **/
def vector : namespace =

	struct vec2d[T]:

		var x : T;
		var y : T;

		constructor(x, y);

		operator <=> +(v : vec2d[T]) : vec2d[T] = return vec2d[T](x + v.x, y + v.y);

		operator <=> +(v : *vec2d[T]) : vec2d[T] = return vec2d[T](x + v->x, y + v->y);

		operator ==> +(s : T) : vec2d[T] = return vec2d[T](x + s, y + s);

		operator ==> -(s : T) : vec2d[T] = return vec2d[T](x - s, y - s);

include vector;

var v1 : vec2d[float] = vec2d[float](2.0, 1.0) // equal to var v1 : vec2d[float] = (2.0, 1.0)
var v2 : vec2d[float](-1.0, 3.0) // calling constructor directly also works

var v3 : vec2d[float] = v1 + v2; // vec2d{x = 1.0, y = 4.0}

// alternativly

include vector as v;

var v1 : v.vec2d[float] = v.vec2d[float](2.0, 1.0)
var v2 : v.vec2d[float](-1.0, 3.0)

var v3 : v.vec2d[float] = v1 + v2;

// alternativly

include vector.{vec2d[float] as fvec}

var v1 : fvec = fvec(2.0, 1.0)
var v2 : fvec(-1.0, 3.0)

var v3 : fvec[float] = v1 + v2;
```
compiler output

```c
struct vec2d_float {
	float x;
	float y;
};

struct vec2d_float vec2d_float_overloadABJEGV(struct vec2d_float * vec2d_float_name, struct vec2d_float v) {
	return (struct vec2d_float){vec2d_float_name->x + v.x, vec2d_float_name->y + v.y};
}

struct vec2d_float vec2d_float_overloadHGGEQO(struct vec2d_float * vec2d_float_name, struct * vec2d_float v) {
	return (struct vec2d_float){vec2d_float_name->x + v->x, vec2d_float_name->y + v->y};
}

struct vec2d_float vec2d_float_overloadABJEGV(struct vec2d_float * vec2d_float_name, float s) {
	return (struct vec2d_float){vec2d_float_name->x + s, vec2d_float_name->y + s};
}

struct vec2d_float v1 = (vec2d_float){.x = 2.0, .y = 1.0};
struct vec2d_float v2 = (vec2d_float){.x = -1.0, .y = 3.0};

struct vec2d_float v3 = vec2d_float_overloadABJEGV(&v1, v2);
```

 - **type parameter namespaces**

```c
def linkedList : namespace[T] =

	/**
	 *  struct node has no type parameter but
	 *  instead relies on the namespace type parameter
	 *
	 *  the syntax 'var next  : *T = NULL' means that when
	 *  a constructor is called and next is not initialized by it
	 *  next should default to 'NULL' in this case
	 **/
	struct node:

		var value : T
		var next  : *T = NULL

		constructor(value)

		/**
		 *   recursive append function
		 *
		 *   '&constructor()' syntax enables direct pointer
		 *    declaration with allocation
		 **/
		operator ==> +=(val : T) : void =
			if ( next == NULL ): next = &node(val)
			else: next += val

		operator +=(list : *node) : void =
			if ( next == NULL ): next = list
			else: next += list

		/**
		 *  list pointer incrementation function
		 *  '&==>' or & before comutativity  setting enforces that
		 *  self is a pointer to an instance of the struct, '#==>' would
		 *  do the oposite and prevent function call if self was a pointer.
		 **/

		operator &==> ++(void) : void =
			if(self != NULL): self = next;

		operator &==> >>(idx : u32) : *node =
			if (idx < 1) return self
			var res : *node = next
			var i : u32
			for(i = 0; i < (idx-1); i++, res++)
			return res


	func printList(list : *node) : void =
		for(var e : *node = list; e != NULL; e++):
			printf("[%(T)]->", e->value)

```
```c

import linkedList[i32] as intList
rename intList.node as intNode

func main( argc : i32, const argv[] : *char) : i32 =
	var head : &intNode(0) /**
                           * same as:
                           * var head : *intNode = malloc(sizeof(intNode))
                           * head->next = NULL;
                           * head->value = 0;
                           **/
	for(i <- 1:10): head += i
	intList.printList(head)
```

**output:**

```shell
[0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->
```
