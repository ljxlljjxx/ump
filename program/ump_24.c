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
int number_update(Number *n);
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
    }
    else
    {
        str->size = len + 2;
        char *new_buf = (char *)malloc(sizeof(char) * str->size);
        strcpy(new_buf + 1, str->buf);
        free(str->buf);
        new_buf[0] = '(';
        new_buf[len] = ')';
        str->buf = new_buf;
    }
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

double op_l[] = {INFINITY, 1.1, 1.1, 2.1, 2.1};
double op_r[] = {INFINITY, 1.0, 1.0, 2.0, 2.0};
const string op_str[] = {
    {1, ""},
    {4, " + "},
    {4, " - "},
    {4, " * "},
    {4, " / "}
};

string string_ans[10000];
size_t ans_cnt;

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

int number_update(Number *n)
{
    switch (n->op)
    {
    case 0:
        n->result.value = n->first.basic;
        break;

    case 1:
        _number_update(&n->first);
        _number_update(&n->second);
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
        n->result.value =  n->first.number->result.value;
        n->result.value *= n->second.number->result.value;
        break;

    case 4:
        _number_update(&n->first);
        _number_update(&n->second);
        n->result.value =  n->first.number->result.value;
        if (n->second.number->result.value)
            n->result.value /= n->second.number->result.value;
        else
            n->result.value = INFINITY;
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

_Number _number_init1(Number *a)
{
    _Number ans;
    ans.number = a;
    return ans;
}

_Number _number_init2(BasicType a)
{
    _Number ans;
    ans.basic = a;
    return ans;
}

Number number_calculate(Number *a, Number *b, int op)
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
    b = number_print(n->first.number);
    if (op_r[n->op] < op_l[bop]) add_bracket(&b);
    ans = string_add(&a, op_str + n->op);
    ans = string_add(&ans, &b);
    return ans;
}

void debug_number_output(Number *a)
{
    printf("first: %p; ", a->first.number);
    printf("second: %p; ", a->second.number);
    printf("op: %d; ", a->op);
    printf("result: %lf\n", a->result.value);
}

int ckeck2(Number *a, Number *b)
{
    int ans = 0;
    Number s;
    for (int i = 1; i <= 4; i++)
    {
        s = number_calculate(a, b, i);
        debug_number_output(&s);
        if (number_equal(&s, n_24p))
        {
            string_ans[ans_cnt++] = number_print(&s);
            ans++;
        }
    }
    return ans;
}

int check3(Number *a, Number *b, Number *c)
{
    int ans = 0;
    Number s;
    for (int i = 1; i <= 4; i++)
    {
        s = number_calculate(a, b, i);
        ans += ckeck2(&s, c);
        ans += ckeck2(c, &s);
    }
    return ans;
}

int check4(Number *a, Number *b, Number *c, Number *d)
{
    int ans = 0;
    Number s;
    for (int i = 1; i <= 4; i++)
    {
        s = number_calculate(a, b, i);
        ans += check3(&s, c, d);
        ans += check3(&s, d, c);
        ans += check3(c, &s, d);
        ans += check3(d, &s, c);
        ans += check3(c, d, &s);
        ans += check3(d, c, &s);
    }
    return ans;
}

int main(int argc, char **argv)
{
    freopen("ump_24.txt", "w", stdout);
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

    for (int i = 0; i < ans_cnt; i++)
    {
        puts(string_ans[i].buf);
    }
    return 0;
}
