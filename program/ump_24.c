#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

struct ResultType;
typedef struct ResultType ResultType;
struct Number;
typedef struct Number Number;
typedef int BasicType;
typedef union _Number
{
    Number *number;
    BasicType basic;
} _Number;
typedef struct string
{
    size_t size;
    char *buf;
} string;
int number_update(Number *);
void debug_number_output(const Number *, int);
int debug_string_check(const string *);
void debug_string_output(const string *);

const string space = {2, " "};
size_t string_length(const string *str)
{
    return strlen(str->buf) + 1;
}

void string_init(string *str, const char *s)
{
    str->size = strlen(s) + 5;
    str->buf = (char *)malloc(sizeof(char) * str->size);
    strcpy(str->buf, s);
}

string string_add(const string *str1, const string *str2)
{
    string ans;
    ans.size = string_length(str1) + string_length(str2);
    ans.buf = (char *)malloc(sizeof(char) * ans.size);
    strcpy(ans.buf, str1->buf);
    strcat(ans.buf, str2->buf);
    assert(debug_string_check(&ans));
    return ans;
}

void add_bracket(string *str)
{
    size_t len = string_length(str);
    if (len <= str->size - 2)
    {
        for (int i = len-2; i >= 0; i--)
        {
            str->buf[i+1] = str->buf[i];
        }
        str->buf[0] = '(';
        str->buf[len] = ')';
        assert(debug_string_check(str));
    }
    else
    {
        str->size = len + 2;
        char *new_buf = (char *)malloc(sizeof(char) * str->size);
        for (int i = 0; i < len-1; i++) new_buf[i+1] = str->buf[i];
        free(str->buf);
        new_buf[0] = '(';
        new_buf[len] = ')';
        new_buf[len+1] = 0;
        str->buf = new_buf;
        assert(debug_string_check(str));
    }
}

void string_resize(string *a)
{
    size_t len = strlen(a->buf);
    for (; a->buf[len] == 32; len--);
    a->size = len + 1;
    a->buf = realloc(a->buf, a->size * sizeof(char));
    a->buf[len] = 0;
}

struct ResultType
{
    double value;
};

const ResultType rt_24 = {24};

int result_equal(const ResultType *a, const ResultType *b)
{
    return a->value == b->value;
}

struct Number
{
    _Number first;
    _Number second;
    int op;
    ResultType result;
};

const Number n_24 = {
    .first = {
        .basic = 24
    },
    .op = 0,
    .result = {
        .value = 24
    }
};

const Number *n_24p = &n_24;

double op_l[] = {INFINITY, 1.0, 1.0, 2.0, 2.0};
double op_r[] = {INFINITY, 1.0, 1.1, 2.0, 2.1};
const string op_str[] = {
    {4, "???"},
    {4, " + "},
    {4, " - "},
    {4, " * "},
    {4, " / "}
};

string string_ans[10000];
size_t ans_cnt;

string *__string_ans[10000];
size_t __ans_cnt;

void number_read_charp(Number *n, char *s)
{
    sscanf(s, "%d", &n->first.basic);
    n->op = 0;
}

void number_read_stdout(Number *n)
{
    scanf("%d", &n->first.basic);
    n->op = 0;
}

int _number_update(_Number *n)
{
    return number_update(n->number);
}

int number_same(Number *a, Number *b)
{
    return a->op == b->op && a->first.basic == b->first.basic && a->second.basic == b->second.basic;
}

int number_compare(const void *_a, const void *_b)
{
    const Number *a = (const Number *)_a;
    const Number *b = (const Number *)_b;
    if (b->op == 0 && a->op == 0) return a->first.basic < b->first.basic;
    if (b->op == 0) return 1;
    if (a->op == 0) return 0;
    if (b->op != a->op) return a->op < b->op;
    if (!number_same(a->first.number, b->first.number)) return number_compare(a->first.number, b->first.number);
    if (!number_same(a->second.number, b->second.number)) return number_compare(a->second.number, b->second.number);
    return 0;
}

int number_update(Number *n)
{
    if (!n->op)
    {
        n->result.value = n->first.basic;
        return 0;
    }
    switch (n->op)
    {
    case 1:
        _number_update(&n->first);
        _number_update(&n->second);
        if (!number_compare(n->first.number, n->second.number))
        {
            Number *t = n->first.number;
            n->first.number = n->second.number;
            n->second.number = t;
        }
        n->result.value =  n->first.number->result.value;
        n->result.value += n->second.number->result.value;
        break;

    case 2:
        _number_update(&n->first);
        _number_update(&n->second);
        n->result.value =  n->first.number->result.value;
        n->result.value -= n->second.number->result.value;
        break;

    case 3:
        _number_update(&n->first);
        _number_update(&n->second);
        if (!number_compare(n->first.number, n->second.number))
        {
            Number *t = n->first.number;
            n->first.number = n->second.number;
            n->second.number = t;
        }
        n->result.value =  n->first.number->result.value;
        n->result.value *= n->second.number->result.value;
        break;

    case 4:
        _number_update(&n->first);
        _number_update(&n->second);
        n->result.value =  n->first.number->result.value;
        if (n->second.number->result.value)
            n->result.value /= n->second.number->result.value;
        else if (n->first.number->result.value)
            n->result.value = INFINITY;
        else
            n->result.value = NAN;
        break;
    
    default:
        assert(0); 
    }
    return 0;
}

int float_equal(double a, double b)
{
    return fabs(a - b) <= 1e-6;
}

int number_equal(const Number *a, const Number *b)
{
    return result_equal(&a->result, &b->result);
}

int nr_equal(Number *a, ResultType *b)
{
    return result_equal(&a->result, b);
}

_Number _number_init1(const Number *a)
{
    _Number ans;
    ans.number = (Number *)a;
    return ans;
}

_Number _number_init2(BasicType a)
{
    _Number ans;
    ans.basic = a;
    return ans;
}

Number number_calculate(const Number *a, const Number *b, int op)
{
    Number ans;
    ans.first = _number_init1(a);
    ans.second = _number_init1(b);
    ans.op = op;
    number_update(&ans);
    return ans;
}

string number_print(Number *n)
{
    string ans;
    static char buf[100];
    if (n->op == 0)
    {
        sprintf(buf, "%d", n->first.basic);
        string_init(&ans, buf);
        return ans;
    }
    int aop = n->first.number->op;
    int bop = n->second.number->op;
    string a, b;
    a = number_print(n->first.number);
    if (op_r[aop] < op_l[n->op]) add_bracket(&a);
    b = number_print(n->second.number);
    if (op_r[n->op] > op_l[bop]) add_bracket(&b);
    ans = string_add(&a, op_str + n->op);
    ans = string_add(&ans, &b);
    return ans;
}

void debug_number_output(const Number *a, int deep)
{
    if (a->op == 0)
    {
        for (int i = 0; i < deep; i++) putchar(9); printf("op: 0; first: %d\n", a->first.basic);
        for (int i = 0; i < deep; i++) putchar(9); printf("result: %lf\n", a->result.value);
        return;
    }
    for (int i = 0; i < deep; i++) putchar(9); printf("first: %p;\n", a->first.number);
    debug_number_output(a->first.number, deep + 1);
    for (int i = 0; i < deep; i++) putchar(9); printf("second: %p;\n", a->second.number);
    debug_number_output(a->second.number, deep + 1);
    for (int i = 0; i < deep; i++) putchar(9); printf("op: %d;\n", a->op);
    for (int i = 0; i < deep; i++) putchar(9); printf("result: %lf\n", a->result.value);
}

void debug_string_output(const string *str)
{
    printf("adr: %p; size: %zd; '%s'\n", str, str->size, str->buf);
}

int debug_string_check(const string *str)
{
    if (string_length(str) <= str->size) return 1;
    debug_string_output(str);
    return 0;
}

int string_cmp(const void *_a, const void *_b)
{
    const string *a = (const string *)_a;
    const string *b = (const string *)_b;
    const char *abuf = a->buf;
    const char *bbuf = b->buf;

    if (a->size != b->size) return (a->size > b->size) * 2 - 1;
    return strcmp(abuf, bbuf);
}

#define _check2(a, b, i) s = number_calculate(a, b, i); \
        if (number_equal(&s, n_24p)) \
        { \
            string_ans[ans_cnt] = number_print(&s); \
            string_resize(ans_cnt + string_ans); \
            ans_cnt++; \
        }

void ckeck2(const Number *a, const Number *b)
{
    int ans = 0;
    Number s;
    _check2(a, b, 1);
    _check2(a, b, 2);
    _check2(b, a, 2);
    _check2(a, b, 3);
    _check2(a, b, 4);
    _check2(b, a, 4);
}

void check3(const Number *a, const Number *b, const Number *c)
{
    Number s;
    for (int i = 1; i <= 4; i++)
    {
        s = number_calculate(a, b, i);
        ckeck2(&s, c);
        ckeck2(c, &s);
    }
}

void check4(const Number *a, const Number *b, const Number *c, const Number *d)
{
    Number s;
    for (int i = 1; i <= 4; i++)
    {
        s = number_calculate(a, b, i);
        check3(&s, c, d);
        check3(&s, d, c);
        check3(c, &s, d);
        check3(d, &s, c);
        check3(c, d, &s);
        check3(d, c, &s);
    }
}

int main(int argc, char **argv)
{
    Number a, b, c, d;
    if (argc == 5)
    {
        number_read_charp(&a, argv[1]);
        number_read_charp(&b, argv[2]);
        number_read_charp(&c, argv[3]);
        number_read_charp(&d, argv[4]);
    }
    else
    {
        number_read_stdout(&a);
        number_read_stdout(&b);
        number_read_stdout(&c);
        number_read_stdout(&d);
    }

    check4(&a, &b, &c, &d);
    check4(&a, &b, &d, &c);
    check4(&a, &c, &b, &d);
    check4(&a, &c, &d, &b);
    check4(&a, &d, &b, &c);
    check4(&a, &d, &c, &b);
    check4(&b, &a, &c, &d);
    check4(&b, &a, &d, &c);
    check4(&b, &c, &a, &d);
    check4(&b, &c, &d, &a);
    check4(&b, &d, &a, &c);
    check4(&b, &d, &c, &a);
    check4(&c, &a, &b, &d);
    check4(&c, &a, &d, &b);
    check4(&c, &b, &a, &d);
    check4(&c, &b, &d, &a);
    check4(&c, &d, &a, &b);
    check4(&c, &d, &b, &a);
    check4(&d, &a, &b, &c);
    check4(&d, &a, &c, &b);
    check4(&d, &b, &a, &c);
    check4(&d, &b, &c, &a);
    check4(&d, &c, &a, &b);
    check4(&d, &c, &b, &a);


    if (ans_cnt == 0)
    {
        puts("No Solutions!");
        return 0;
    }

    qsort(string_ans, ans_cnt, sizeof(*string_ans), string_cmp);

    __string_ans[__ans_cnt++] = &string_ans[0];
    for (int i = 1; i < ans_cnt; i++)
    {
        if (strcmp(string_ans[i-1].buf, string_ans[i].buf))
            __string_ans[__ans_cnt++] = &string_ans[i];
    }

    if (__ans_cnt == 1)
        puts("There are a total of 1 solution, as follows:");
    else
        printf("There are a total of %zd solutions, as follows:\n", __ans_cnt);

    for (int i = 0; i < __ans_cnt; i++)
    {
        puts(__string_ans[i]->buf);
    }
    return 0;
}
