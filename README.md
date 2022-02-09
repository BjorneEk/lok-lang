# lok-lang

a plan for a "programing language" that compiles to c code.


the purpouse of the language is to modernize the syntax and make it more uniform as well as extend it with a few features that makes the code both more consise and more verbose at the same time. The most important of these features is the ability to overload functions.

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
 - **Advanced structs**

more class like struct functionality<br>
syntax:

```javascript
	struct vec2d[T]:

		var x : T;
		var y : T;

		constructor(x, y);

		overload:
			def +(v : vec2d[T]) : vec2d[T] = return vec2d[T](x + v.x, y + v.y);

			def +(v : *vec2d[T]) : vec2d[T] = return vec2d[T](x + v->x, y + v->y);

			def +(s : T) : vec2d[T] = return vec2d[T](x + s, y + s);

	var v1 : vec2d[float](2.0, 1.0) // equal to var v1 : vec2d[float] = (2.0, 1.0)
	var v2 : vec2d[float](-1.0, 3.0)

	var v3 : vec2d[float] = v1 + v2; // vec2d{x = 1.0, y = 4.0}
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
