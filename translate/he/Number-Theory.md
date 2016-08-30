# Số học

[[_TOC_]]

# Giới thiệu
Các bài toán trong lập trình thi đấu mà liên quan đến Toán học thường sẽ rơi vào hai mảng là số học và hình học. Nếu bạn biết nhiều về số học, bạn sẽ có khả năng giải quyết nhiều bài toán khó và một nền tảng tốt để giải quyết nhiều bài toán khác.

Các bài toán trong lập trình thi đấu thường đòi hỏi bạn một cái nhìn sâu sắc, vì vậy chỉ biết một số vấn đề về số học là không đủ. Mọi bài toán đều đều yêu cầu bạn phải biết một lượng kiến thức toán nhất định. Ví dụ, một số bài toán yêu cầu bạn phải giải một hệ nhiều phương trình hay tính xấp xỉ nghiệm của nhiều phương trình khác nhau.

# Đồng dư thức (Modulo)
Phép đồng dư thức cho bạn số dư của phép chia số này cho số khác. Dấu của phép đồng dư thức là $\%$.

Ví dụ:

Ta có hai số 5 và 2, khi đó $5\%2$ bằng 1 do khi chia 5 cho 2, ta được số dư là 1.

Tính chất:
Đồng dư thức có một số tính chất sau:

$(a+b)\%c = a\%c + b\%c$

$(a.b)\%c = ((a\%c).(b\%c))\%c$

Ví dụ:

Giả sử $a=5,b=3,c=2$

Khi đó:

- $(5+3)\%2=8\%2=0$

và cũng bằng $(5\%2+3\%2)\%2=(1+1)\%2=0$.

- $(5.3)\%2=15\%2=1$

và cũng bằng $((5\%2).(3\%2))\%2=(1.1)\%2=1$.

# Ước chung lớn nhất

Ước chung lớn nhất (GCD) của hai hay nhiều số là số nguyên dương lớn nhất mà là ước chung của tất cả các số đó.

Ví dụ: GCD của 6 và 10 là 2 vì 2 là số nguyên dương lớn nhất mà là ước chung của 6 và 10.

## Thuật toán "ngây thơ"

Ta có thể duyệt tất cả các số từ $min(A,B)$ đến 1 và kiểm tra xem số đang xét có phải là ước của của $A$ và $B$ hay không. Nếu đúng như vậy thì số đang xét sẽ là GCD của $A$ và $B$.

```cpp
int GCD(int A, int B) {
    int m = min(A, B), gcd;
    for(int i = m; i > 0; --i)
        if(A % i == 0 && B % i == 0) {
            gcd = i;
            return gcd;
        }
}
```

Độ phức tạp của thuật toán: $O(min(A,B))$.

## Thuật toán Euclid

Thuật toán Euclid dựa trên tính chất sau của ước chung lớn nhất $GCD(A,B)=GCD(B,A\%B)$. Thuật toán sẽ quy nạp cho đến khi $A\%B=0$.

```cpp
int GCD(int A, int B) {
    if(B==0)
        return A;
    else
        return GCD(B, A % B);
}
```

Ví dụ:

Giả sử $A=16, B=10$.

$GCD(16,10)=GCD(10,16\%10)=GCD(10,6)$

$GCD(10,6)=GCD(6,10\%6)=GCD(6,4)$

$GCD(6, 4) = GCD(4, 6 \% 4) = GCD(4, 2)$

$GCD(4, 2) = GCD(2, 4 \% 2) = GCD(2, 0)$

Vì $B=0$ nên $GCD(2,0)$ sẽ trả về giá trị 2.

Độ phức tạp của thuật toán: $O(\log{max(A,B)})$.

## Thuật toán Euclid mở rộng

Đây là một thuật toán mở rộng của thuật toán Euclid ở trên. $GCD(A,B)$ có một tính chất rất đặc biệt: Nó luôn có thể được biểu diễn dưới dạng phương trình $Ax+By=GCD(A,B)$.

Thuật toán sẽ cho ta biết một cặp giá trị $(x;y)$ thỏa mãn phương trình này và nhờ đó giúp ta tính Modular Multiplicative Inverse. $x$ và $y$ có thể có giá trị bằng không hoặc âm. Chương trình sau đọc hai số $A$ và $B$ và in ra $GCD(A,B)$ cũng như một cặp số $(x;y)$ thỏa mãn phương trình.

```cpp
#include < iostream >

int d, x, y;
void extendedEuclid(int A, int B) {
    if(B == 0) {
        d = A;
        x = 1;
        y = 0;
    }
    else {
        extendedEuclid(B, A%B);
        int temp = x;
        x = y;
        y = temp - (A/B)*y;
    }
}

int main( ) {
extendedEuclid(16, 10);
cout << ”The GCD of 16 and 10 is ” << d << endl;
cout << ”Coefficient x and y are: ”<< x <<  “and  “ << y << endl;
return 0;
}
```

Kết quả

```
The GCD of 16 and 10 is 2
Coefficient x and y are: 2 and -3
``` 

Ban đầu, thuật toán Euclid mở rộng sẽ chạy như thuật toán Euclid cho đến khi ta có $GCD(A,B)$ hoặc cho đến khi $B$ bằng 0 và khi đó thuật toán sẽ đặt $x=1$ và $y=0$. Vì $B=0$ và $GCD(A,B)$ là $A$ trong thời điểm hiện tại nên phương trình $Ax+By=0$ trở thành $A.1+0.0=A$.

Giá trị của các biến $d,x,y$ trong hàm `extendedEuclid()` sẽ lần lượt trở thành:

1. $d=2, x = 1, y = 0$.

2. $d=2, x = 0 , y = 1 - (4/2).0 = 1$.

3. $d=2, x = 1 , y = 0 - (6/4).1 = -1$.

4. $d=2, x = -1 , y = 1 - (10/6).(-1) = 2$.

5. $d=2 , x= 2, y = -1 - (16/10).2 = -3$

Độ phức tạp của thuật toán: Độ phức tạp của thuật toán Euclid mở rộng là $O(\log{max(A,B)})$.

# Số nguyên tố

Số nguyên tố là số nguyên lớn hơn 1 và có đúng 2 ước là 1 và chính nó.

Hợp số là số nguyên lớn hơn 1 và có nhiều hơn 2 ước.

Ví dụ, 5 là số nguyên tố vì 5 chỉ chia hết cho 1 và 5. Tuy nhiên, 6 là hợp số vì 6 chia hết cho 1, 2, 3 và 6.

Có rất nhiều phương pháp để kiểm tra một số nguyên có phải là số nguyên tố hay không.

## Thuật toán "ngây thơ"

Ta sẽ duyệt hết tất cả các số từ 1 đến $N$ và đếm số ước của $N$. Nếu số ước của $N$ là 2 thì $N$ là số nguyên tố, nếu không thì $N$ không là số nguyên tố.

```cpp
void checkprime(int N){
    int count = 0;
    for( int i = 1;i <= N;++i )
        if( N % i == 0 )
            count++;
    if(count == 2)
        cout << N << “ is a prime number.” << endl;
    else
        cout << N << “ is not a prime number.” << endl;
}
```

Độ phức tạp của thuật toán: Độ phức tạp của thuật toán là $O(N)$ do ta phải duyệt hết các số từ 1 đến $N$.

Một thuật toán tốt hơn:

Xét hai số nguyên dương $N$ và $D$ thỏa mãn $N$ chia hết cho $D$ và $D$ nhỏ hơn $\sqrt{N}$. Khi đó $\frac{N}{D}$ phải lớn hơn $\sqrt{N}$. $N$ cũng chia hết cho $\frac{N}{D}$. Vì thế, nếu $N$ có ước nhỏ hơn $\sqrt{N}$ thì $N$ cũng có ước lớn hơn $\sqrt{N}$. Do đó, ta chỉ cần duyệt đến $\sqrt{N}$.

```cpp
void checkprime(int N) {
    int count = 0;
    for( int i = 1;i * i <=N;++i ) {
         if( N % i == 0) {
         if( i * i == N )
                     count++;
                 else                                                     // i < sqrt(N) and (N / i) > sqrt(N)
                     count += 2;
      }
    }
    if(count == 2)
        cout << N << “ is a prime number.” << endl;
    else
        cout << N << “ is not a prime number.” << endl;
}
```

Độ phức tạp của thuật toán: Độ phức tạp của thuật toán là $O(\sqrt{N})$ do ta phải duyệt từ 1 đến $\sqrt{N}$.

## Sàng Eratosthenes

Sàng Eratosthenes dùng để tìm các số nguyên tố nhỏ hơn hoặc bằng số nguyên $N$ nào đó. Nó còn có thể được sử dụng để kiểm tra một số nguyên nhỏ hơn hoặc bằng $N$ hay không.

[[https://upload.wikimedia.org/wikipedia/commons/b/b8/Animation_Sieb_des_Eratosthenes_%28vi%29.gif|alt=text]]

Nguyên lí hoạt động của sàng là vào mỗi lần duyệt, ta chọn một số nguyên tố và loại ra khỏi sàng tất cả các bội của số nguyên tố đó mà lớn hơn số đó. Sau khi duyệt xong, các số còn lại trong sàng đều là số nguyên tố.

Mã giả:

- Đánh dấu tất cả các số đều là số nguyên tố.

- Với mỗi số nguyên tố nhỏ hơn $\sqrt{N}$

   - Đánh dấu các bội lớn hơn nó là số nguyên tố.

```cpp
void sieve(int N) {
    bool isPrime[N+1];
    for(int i = 0; i <= N;++i) {
        isPrime[i] = true;
    }
    isPrime[0] = false;
    isPrime[1] = false;
    for(int i = 2; i * i <= N; ++i) {
         if(isPrime[i] == true) {
             // Mark all the multiples of i as composite numbers
             for(int j = i * i; j <= N ;j += i)
                 isPrime[j] = false;
        }
    }
}
```

Code trên được dùng để tìm các số nguyên tố nhỏ hơn hoặc bằng $N$.

Độ phức tạp của thuật toán:

Số lần lặp của vòng lặp trong là:

Khi $i=2$, vòng lặp trong lặp $\frac{N}{2}$ lần.

Khi $i=3$, vòng lặp trong lặp $\frac{N}{3}$ lần.

Khi $i=5$, vòng lặp trong lặp $\frac{N}{5}$ lần.

.

.

.

Độ phức tạp tổng: $N.(\frac{1}{2}+\frac{1}{3}+\frac{1}{5}+...)=O(N\log{\log{N}})$.

#Đồng dư thức với lũy thừa

Xét bài toán tính $a^b\%c$, với $\%$ là dấu đồng dư thức và $b$ có thể rất lớn (ví dụ $b \leq 10^{18}$).

## Thuật toán "ngây thơ"

$a^b$ có thể viết là $a.a.a.a...$ với $b$ chữ $a$. Do đó ta có thể nhân $b$ lần $a$ để có được kết quả.

```cpp
long long exponentiation(long long a, long long b, long long c) {
        long long ans = 1;
        for(int i = 1;i <= b;i++) {
            ans *= a;                             //multiplying a, b times.
            ans %= c;
        }
    return ans;
 }
```
Trong mỗi lần lặp, biến $ans$ chứa kết quả được nhân với $a$. Ngoài ra, ta cần đảm bảo $a$ sẽ không vượt quá $c$ trong các lần lặp, vì thế ta lấy phần dư khi chia $ans$ cho $c$ (`ans = ans % c`). Ta làm được vậy là nhờ tính chất $(x.y) \% n = ((x \% n).(y \% n)) \% n$.

Vì vậy trong code trên ta tính $(ans.a)\%c$ bằng cách tính $((ans\%c).(a\%c))\%c$.

Độ phức tạp của thuật toán: $O(b)$.

## Thuật toán "chia để trị"

Dễ dàng nhận thấy thuật toán trên không hiệu quả, vì thế ta cần tìm thuật toán hiệu quả hơn. Ta có thể giải bài toán này với độ phức tạp $O(\log_{2}{b})$ bằng kĩ thuật lũy thừa bằng cách bình phương. Kĩ thuật này chỉ cần $O(\log_{2}{b})$ lần bình phương và $O(\log_{2}{b})$ phép nhân để ra kết quả. Rõ ràng cách giải này hiệu quả hơn nhiều lần so với thuật toán "ngây thơ".

Ta biết rằng $a^b$ có thể được viết dưới dạng:

$a^b=(a^{\frac{b}{2}})^2$ nếu $b$ chia hết cho 2.

$a^b=a.(a^{[\frac{b}{2}]})^2$ nếu $b$ không chia hết cho 2.

$a^b=1$ nếu $b=0$.

```cpp
int sqr(int x)
{
	return x*x;
}
int pow(int a,int b,int c)
{
	if (b==0)
		return 1%c; // c co the bang 1.
	else
	if (b%2==0)
		return sqr(pow(a,b/2))%c; // tranh goi pow(a,b/2) 2 lan -> TLE
	else
		return a*(sqr(pow(a,b/2))%c)%c;
}
```
Giả sử ta có $a=2,b=5,c=5$, khi đó kết quả là $pow(2,5,5)$

1. Do $b$ lẻ, nên hàm $pow(2,5,5)$ gọi hàm $pow(2,2,5)$ để tính $2.pow(2,2,5)$

2. Trong hàm $pow(2,2,5)$, do $b=2$ chẵn nên $pow(2,2,5)=pow(2,1,5)^2$

3. Trong hàm $pow(2,1,5)$, do $b=1$ lẻ nên $pow(2,1,5)=2*pow(2,0,5)$.

4. Trong hàm $pow(2,0,5)$, do $b=0$ nên ta trả về 1.

5. Quay lại hàm $pow(2,1,5)$: hàm này trả về giá trị 2.

6. Quay lại hàm $pow(2,2,5)$: hàm này trả về giá trị 4.

7. Quay lại hàm $pow(2,5,5)$: hàm này trả về giá trị $(2.4^2)\%5=32\%5=2$.

Vậy ta có $2^5\%5=2$. 

Độ phức tạp của thuật toán: $O(\log_{2}{b})$

# Lí thuyết tập hợp

## Tập hợp là gì?

Trong toán học, tập hợp là một nhóm các phần tử, mỗi phần tử phân biệt với nhau.

Ví dụ, 2, 4, 6 được coi là các phần tử phân biệt khi ta xét từng số một, nhưng khi chúng ta nhóm ba số ấy thì ta được một tập hợp gồm ba phần tử được kí hiệu là {2;4;6}.

Tập hợp là một trong những khái niệm cơ bản trong Toán học.

![](https://d320jcjashajb2.cloudfront.net/media/uploads/0fed95c.png)

Tập hợp các hình đa giác được biểu diễn trong biểu đồ Venn.

## Tập con

Nếu mọi phần tử thuộc tập $A$ cũng thuộc tập hợp $B$, thì tập $A$ là tập con của tập $B$, kí hiệu là $A \subset B$.

Tương tự, ta có thể viết $B \supset A$, đọc là $B$ là tập cha của tập $A$.

Quan hệ cha-con giữa các tập hợp còn được gọi là quan hệ chứa nhau hay quan hệ bao hàm.

Nếu $A$ là tập con của tập $B$ nhưng không bằng tập $B$, thì $A$ được gọi là tập con không tầm thường của tập $B$, kí hiệu là $A \subsetneq B$, hay $B \supsetneq A$ (đọc là $B$ là tập cha không tầm thường của tập $A$).

Ví dụ:

- {1;3} $\subset$ {1;2;3;4}

- {1;2;3;4} $\subset$ {1;2;3;4}

Tập rỗng (kí hiệu $\varnothing$) là tập con của tất că các tập và tất cả các tập là tập con của chính nó:

- $\varnothing \subset A$.

- $A \subset A$.

![](https://d320jcjashajb2.cloudfront.net/media/uploads/668b06c.png)

$A$ là tập con của tập $B$.

## Các phép toán với tập hợp

Có nhiều phép toán có khả năng xây dựng một tập hợp mới dựa trên các tập hợp đã cho.

### Phép hợp

Hai tập hợp có thể được ghép vào nhau. Hợp của hai tập hợp $A$ và $B$, kí hiệu là $A \cup B$, là một tập hợp gồm các phần tử thuộc tập $A$ hoặc thuộc tập $B$.

Ví dụ:

- {1;2} $\cup$ {1;2} = {1;2}

- {1;2} $\cup$ {2;3} = {1;2;3}

- {1;2;3} $\cup$ {3;4;5} = {1;2;3;4;5}

![](https://d320jcjashajb2.cloudfront.net/media/uploads/94410aa.PNG)

Hợp của hai tập hợp $A$ và $B$, kí hiệu là $A \cup B$.

Một vài tính chất cơ bản của phép hợp:

- $A \cup B = B \cup A$.

- $(A \cup B) \cup C = A \cup (B \cup C)$.

- $A \subset (A \cup B)$.

- $A \cup A = A$.

- $A \subset B$ khi và chỉ khi $A \cup B = B$.

### Phép giao

Một tập hợp mới có thể được xây dựng từ các phẩn tử mà cả hai tập đều có. Giao cuả hai tập hợp $A$ và $B$, kí hiệu $A \cap B$, là tập hợp các phần tử cùng thuộc tập $A$ và tập $B$. Nếu $A \cap B = \varnothing$, tập $A$ và tập $B$ là hai tập rời nhau.

Ví dụ:

- {1;2} $\cap$ {1;2} = {1;2}.

- {1;2} $\cap$ {2;3} = {2}.

![](https://d320jcjashajb2.cloudfront.net/media/uploads/618200f.png)

Giao của hai tập hợp $A$ và $B$, kí hiệu là $A \cap B$.

Một vài tính chất cơ bản của phép hợp:

- $A \cap B = B \cap A$.

- $(A \cap B) \cap C = A \cap (B \cap C)$.

- $A \cap B \subset A$.

- $A \cap A = A$.

- $A \cap \varnothing = \varnothing$.

- $A \subset B$ khi và chỉ khi $A \cap B = A$.

### Phép lấy hiệu

Ta có thể thực hiên phép trừ với hai tập hợp. Hiệu của hai tập hợp $A$ và $B$, kí hiệu là $A \backslash B$, là tập hợp bao gồm tất cả các phần tử thuộc $A$ nhưng không thuộc $B$. Lưu ý rằng ta có thể trừ phần tử mà không thuộc tập hợp, ví dụ như bỏ phần tử 'xanh' khỏi tập hợp {1;2;3}, khi đó tập hợp {1;2;3} không bị thay đổi.

Trong một số trường hợp tập $A$ được coi là tập con của một tập $U$ lớn hơn. Trong trường hợp đó, $U \backslash A$ được gọi là phần bù hoàn toàn (absolute complement) của tập $A$, và được kí hiệu là $A'$.

Ví dụ:

- {1;2} $\backslash$ {1;2} = $\varnothing$.

- {1;2;3;4} $\backslash$ {1;3} = {2;4}. 

- Nếu $U$ là tập hợp các số nguyên, $E$ là tập hợp các số nguyên chẵn, $O$ là tập hợp các số nguyên lẻ, khi đó $U \backslash E = E' = O$.

![](https://d320jcjashajb2.cloudfront.net/media/uploads/6669f13.png)

Hiệu của hai tập hợp $A$ và $B$.

![](https://d320jcjashajb2.cloudfront.net/media/uploads/7fe7571.png)

Phần bù của $A$ trong $U$.

Một vài tính chất cơ bản của phép lấy hiệu

- $A \backslash B \ne B \backslash A$ với $A \ne B$.

- $A \cup A' = U$.

- $A \cap A' = \varnothing$.

- $(A')' = A$.

- $A \backslash A = \varnothing$.

- $A \backslash B = A \cap B'$.

- $U' = \varnothing$ và $\varnothing' = U$.

# Các kiến thức cơ bản về Tổ hợp

Kí hiệu $|A|$ là số phần tử của tập $A$ (hay còn được gọi là lực lượng của tập $A$).

Một vài quy tắc về tổ hợp cần nhớ:

1. Quy tắc nhân:
Giả sử có hai tập hợp $A$ và $B$. Khi đó số cách chọn cặp gồm một phần tử thuộc tập $A$ và một phần tử thuộc tập $B$ là $|A|.|B|$

2. Quy tắc cộng: Giả sử có hai tập hợp $A$ và $B$. Khi đó số cách chọn một phần tử thuộc tập $A$ hoặc thuộc tập $B$ là $|A|+|B|$ nếu hai tập $A$ và $B$ rời nhau.

3. Quy tắc cộng mở rộng: $|A \cup B| = |A| + |B| - |A \cap B|$.

Trong trường hợp tổng quát, ta có:

$|\bigcup_{i=1}^n A_i| = \sum_{i=1}^n |A_i| - \sum_{i \ne j} |A_i \cap A_j| + |A_1 \cap A_2 \cap A_3| + |A_1 \cap A_2 \cap A_4| + ... + |A_{n-2} \cap A_{n-1} \cap A_n| - ... -$
$ (-1)^n|A_1 \cap A_2 \cap ... \cap A_n|$

Lí do ta phải cộng trừ giao của một số tập hợp vì nếu ta không làm như vậy, ta có thể đếm nhiều lần các phần tử xuất hiện tại nhiều tập hợp khác nhau.

Các quy tắc trên cũng đúng khi ta có ba hay nhiều tập hợp.

## Các kiến thức cơ bản về Chỉnh hợp và Hoán vị

### Chỉnh hợp không lặp

Cho tập hợp $A$ gồm $n$ phần tử. Mỗi bộ gồm $k$ ($0 \leq k \leq n$) phần tử được sắp thứ tự của tập hợp $A$ được gọi là một chỉnh hợp chập $k$ của $n$ phần tử thuộc $A$.

Ví dụ: Trong trận chung kết bóng đá phải phân định thắng thua bằng đá luân lưu 11 mét. Huấn luyện viên của mỗi đội cần trình với trọng tài một danh sách sắp thứ tự 5 cầu thủ trong số 11 cầu thủ để đá luân lưu 5 quả 11 mét.

Mỗi danh sách có xếp thứ tự 5 cầu thủ được gọi là một chỉnh hợp chập 5 của 11 cầu thủ.

Kí hiệu số chỉnh hợp chập $k$ của $n$ phần tử là $A_n^k$.

Số chỉnh hợp chập $k$ của $n$ phần tử được tính bởi công thức

$A_n^k = n(n-1)...(n-k+1) = \frac{n!}{(n-k)!}$.

với $n!=1.2.3...n$ và $0! = 1$.

### Hoán vị không lặp

Mỗi một chỉnh hợp chập $n$ của $n$ phần tử là một hoán vị của $n$ phần tử đó.

Kí hiệu số hoán vị của $n$ phần tử là $P_n$.

Số hoán vị của $n$ được tính bởi công thức:

$P_n = n!$.

### Hoán vị lặp

Hoán vị trong đó mỗi phần tử xuất hiện ít nhất một lần được gọi là hoán vị lặp.

Số hoán vị lặp của $n$ phần tử thuộc $k$ loại, mà các phần tử loại $i$ ($1 \leq i \leq k$) xuất hiện $n_i$ lần được kí hiệu là $P(n_1,n_2,...,n_k)$ và được tính bằng công thức

$P(n_1,n_2,...,n_k) = \frac{n!}{n_1!n_2!...n_k!}$

## Các đối tượng tổ hợp

Một song ánh là tương ứng một-một giữa hai tập hợp, ví dụ tập hợp những người chồng và tập hợp những người vợ (một chồng chỉ có một vợ, và một vợ chỉ có đúng một chồng). Do đó, nếu bạn biết được lực lượng của một tập hợp, bạn có thể biết được lực lượng của tập kia. Ta có thể sử dụng tính chất này trong nhiều bài toán Tổ hợp, đặc biệt là các bài toán đếm, nhưng trước tiên, ta phải biết tính lực lượng của một tập các đối tượng tổ hợp.

### Tổ hợp không lặp

Trong tổ hợp, ta thường phải chọn một tập các phần tử nào đó và không quan tâm đến thứ tự của chúng. Số lượng tập con $k$ phần tử của một tập $n$ phần tử (còn gọi là số tổ hợp chập $k$ của $n$ phần tử) là:

$\binom{n}{k} = C^k_n = \frac{n!}{k!(n-k)!}$

### Tổ hợp có lặp

Giả sử ta cần chọn $k$ phần tử từ một tập $n$ phần tử, không quan trọng thứ tự và một phần tử có thể được chọn nhiều lần. Khi đó, số cách chọn là số tổ hợp lặp chập $k$ của $n$ phần tử và có giá trị là:

$\overline{C^k_n} = \binom{n+k-1}{k} = \frac{(n+k-1)!}{k!(n-1)!}$

Một tính chất thú vị về số tổ hợp có lặp: $\overline{C^k_n}$ là số nghiệm nguyên không âm của phương trình: $x_1+x_2+...+x_n = k$ với $k$ là hằng số nguyên dương.

## Vector nhị phân

Vector nhị phân là kiểu dữ liệu ``<bitset>`` trong C++ STL.

Ngoài ra, các tính chất về tổ hợp của vector nhị phân cũng rất quan trọng. Sau đây là một số tính chất hay được sử dụng của vector nhị phân.

1. Số lượng vector nhị phân độ dài $n$ là $2^n$.

2. Số lượng vector nhị phân độ dài $n$ có $k$ số 1 là $\binom{n}{k}$, vì ta chọn $k$ vị trí có số 1 trong $n$ vị trí.

3. Số lượng cặp vector nhị phân $(a;b)$ (có quan tâm đến thứ tự) thỏa mãn điều kiện khoảng cách giữa $a$ và $b$ là $k$ là $\binom{n}{k}.2^n$.

Khoảng cách giữa hai vector nhị phân $a$ và $b$ là số lượng giá trị $i$ nguyên không âm thỏa mãn $a_i \ne b_i$

## Hệ thức truy hồi

Hệ thức truy hồi là công cụ hỗ trợ đắc lực trong các bài toán đếm. Truy hồi còn giúp ta định nghĩa được nhiều cấu trúc như cây, danh sách, công thức quy hoạch động hay các thuật toán "chia để trị", nên truy hồi được sử dụng rất nhiều trong tin học.

Hệ thức truy hồi là một phương trình dùng để xác định dãy số hoặc hàm số bằng cách dùng các số hạng trước để định nghĩa số hạng sau. Nó rất hữu dụng vì nhiều dãy số có thể dễ dàng được định nghĩa bằng hệ thức truy hồi:

- Hàm đa thức: $a_n=a_{n-1}+1, a_1=1 \rightarrow a_n=n$.

- Hàm mũ: $a_n=2a_{n-1}, a_1=2 \rightarrow a_n=2^n$.

- Giai thừa: $a_n=n.a_{n-1}, a_1 = 1 \rightarrow a_n=n!$.

Ta thường dễ dàng tìm được hệ thức truy hồi để giải các bài toán đếm. Giải hệ thức truy hồi để có được dạng công thức cần tìm là cả một nghệ thuật, tuy vậy ta có thể sử dụng trực tiếp hệ thức truy hồi để giải một số bài toán đơn giản.

## Hệ số nhị thức

Hệ số nhị thức $\binom{n}{k}$ được sử dụng để đếm số cách chọn $k$ vật trong số $n$ vật.

### Đếm số đường đi trên lưới.

Có bao nhiêu cách để đi từ góc trái trên của một bảng $n * m$ ô đến góc phải dưới của ô đó, nếu ta chỉ được phép đi về bên phải hoặc đi xuống dưới. Ta thấy mọi đường đi hợp lệ có $n+m$ bước, và hai đường đi khác nhau nếu và chỉ nếu chúng có một bước đi xuống dưới khác nhau, vậy ta có $\binom{n+m}{n}$ cách đi.

Tính hệ số nhị thức có thể gây tràn số ở các bước trung gian, vì vậy ta nên tính hệ số nhị thức bằng công thức: $\binom{n}{k}=\binom{n-1}{k-1}+\binom{n-1}{k}$

## Một vài dãy số đếm khác

### Dãy số Catalan

Định nghĩa: $C_n=\sum_{k=0}^{n-1} C_kC_{n-1-k}=\frac{1}{n+1}\binom{2n}{n}$

Các ứng dụng của dãy số Catalan:

- Cho một đa giác lồi $n+2$ đỉnh, ta chia đa giác thành các tam giác bằng cách vẽ các đường chéo không cắt nhau trong đa giác. $C_n$ là số cách chia như vậy.

Ví dụ: $n=4$

[![Screenshotfrom2016-08-3011-02-47.png](http://www.upsieutoc.com/images/2016/08/30/Screenshotfrom2016-08-3011-02-47.png)](http://www.upsieutoc.com/image/5zZ8)

- $C_n$ là số các từ Dyck có độ dài $2n$. Từ Dyck là từ gồm $n$ chữ X và $n$ chữ Y sao cho với mọi tiền tố của từ đó, số lượng chữ X không ít hơn số lượng chữ Y. Ví dụ, $C_3 = 5$ từ sau đây là từ Dyck độ dài 6: XXXYYY, XYXXYY, XYXYXY, XXYYXY, XXYXYY.

- Thay mỗi chữ X trong từ Dyck thành dấu mở ngoặc đơn, mỗi chữ Y thành dấu đóng ngoặc đơn, khi đó mỗi từ Dyck trở thành một dãy ngoặc hợp lệ. Vậy $C_n$ còn đếm số dãy ngoặc hợp lệ gồm $n$ cặp ngoặc: ((())), ()(()), ()()(), (())(), (()()).

- $C_n$ còn là số cách đặt ngoặc cho một biểu thức gồm $n+1$ thừa số. Ví dụ với $n=3$, ta có 5 cách đặt ngoặc cho 4 thừa số: $((ab)c)d, (a(bc))d, (ab)(cd), a((bc)d), a(b(cd))$.

- $C_n$ còn là số cây nhị phân đầy đủ có $n$ là (một cây nhị phân được gọi là đầy đủ nếu mọi nút của nó có hai nút con hoặc không có nút con nào). 

![](https://upload.wikimedia.org/wikipedia/commons/0/01/Catalan_number_binary_tree_example.png)

[Và còn nhiều ứng dụng khác...](https://en.wikipedia.org/wiki/Catalan_number#Applications_in_combinatorics)

### Số Euler

Số Euler $\big \langle^n_k \big \rangle$ là số lượng hoán vị các số từ 1 đến $n$ mà có đúng $k$ phần tử lớn hơn phần tử đứng trước nó. Hệ thức truy hồi tính số Euler được lập bằng cách xét mỗi hoán vị $p$ của 1,2,...,$n-1$. Có $n$ vị trí để thêm số $n$ vào hoán vị, và một cách thêm số $n$ có thể làm tăng số phần tử lớn hơn phần tử đứng trước nó của $p$, hoặc bảo toàn số phần tử lớn hơn phần tử đứng trước nó. Vì vậy, 

![$\big \langle^n_k \big \rangle = k\big \langle^{n-1}_k \big \rangle + (n-k+1) \big \langle^{n-1}_{k-1} \big \rangle$](https://d320jcjashajb2.cloudfront.net/media/uploads/93df5ba.gif)

### Bài toán phân tích một số nguyên 

Ta xét bài toán sau:

Cho một số nguyên $n$. Hãy cho biết có bao nhiêu cách phân tích số $n$ thành tổng của dãy các số nguyên dương, các cách phân tích là hoán vị của nhau chỉ tính là một cách.

Ví dụ: $n=5$ có 7 cách phân tích:

1. $5 = 1+1+1+1+1$

2. $5 = 1+1+1+2$

3. $5=1+1+3$

4. $5=1+2+2$

5. $5=1+4$

6. $5=2+3$

7. $5=5$

Cách dễ nhất để đếm số cách phân tích số $n$ là định nghĩa hàm $f(n,k)$ là số cách phân tích số $n$ thành tổng của các số nguyên dương nhỏ hơn hoặc bằng $k$. Các cách phân tích số $n$ thành tổng cách số nguyên dương nhỏ hơn hoặc bằng $k$ có thể chia làm hai loại: chứa số $k$ trong phép phân tích và không chứa số $k$ trong phép phân tích, vì thế ta có $f(n,k)=f(n-k,k)+f(n,k-1)$. Ngoài ra, ta còn dễ dàng có được $f(1,1)=1$ và $f(n,k)=0$ với $k>n$. 

# Các kiến thức cơ bản về Xác suất

Làm việc với xác suất giống như làm một thí nghiệm. Một kết quả là một kết quả của một phép thử hay sự xảy ra hay không xảy ra của một hiện tượng nào đó. Tập hợp tất cả các kết qủa có thể xảy ra của một phép thử được gọi là không gian mẫu, thường được kí hiệu là $\Omega$. Mỗi kết quả có thể của một phép thử được biểu diễn bởi một và chỉ một điểm trong không gian mẫu.

Một số phép thử ví dụ:

- Gieo một con súc sắc một lần: Không gian mẫu là $\Omega$ = {1; 2; 3; 4; 5; 6}.

- Gieo hai đồng xu phân biệt: Không gian mẫu là $\Omega$ = {(Ngửa, Ngửa), (Ngửa, Sấp), (Sấp, Ngửa), (Sấp, Sấp)}.

Ta định nghĩa biến cố là một tập hợp các kết quả của một phép thử. Do đó, một biến cố là một tập con của không gian mẫu. Nếu ta kí hiệu một biến cố là $\Omega_A$, thì $\Omega_A \subset \Omega$. Nếu một biến cố chỉ gồm một kết quả trong không gian mẫu, thì nó được gọi là biến cố đơn. Nếu một biến cố gồm nhiều kết quả trong không gian mẫu thì nó được gọi là biến cố phức.

Thứ mà ta quan tâm nhất là xác suất xảy ra của một biến cố, kí hiệu là $P(A)$. Theo định nghĩa, $P(A)$ là một số thực nằm trong đoạn từ 0 đến 1, với 0 nghĩa là biến cố không thể xảy ra và 1 nghĩa là biến cố chắc chắn xảy ra (nghĩa là biến cố bằng không gian mẫu).

Như đã nói ở trước, mỗi kết qủa được biểu diễn bằng đúng một điểm trong không gian mẫu. Vì thế ta có công thức: $P(A) = \frac{|\Omega_A|}{|\Omega|}$.

## Biến cố độc lập

Hai biến cố được gọi là độc lập với nhau nếu việc xảy ra hay không xảy ra của biến cố này không làm ảnh hưởng tới xác suất xảy ra của biến cố kia.

Ví dụ bạn gieo một con súc sắc và một đồng xu. Xác suất nhận được một số nào đó từ con súc sắc không làm ảnh hưởng đến xác suất đồng xu lật sấp hay lật ngửa. Do đó biến cố gieo con súc sắc được 6 điểm và biến cố đồng xu lật ngửa là hai biến cố độc lập với nhau.

![](https://d320jcjashajb2.cloudfront.net/media/uploads/869de1c.gif)

Nếu hai biến cố $A$ và $B$ độc lập với nhau, không biến cố nào ảnh hưởng đến biến cố nào, khi đó ta có thể viết: $P(A \cup B) = P(A).P(B)$.

# Bài tập áp dụng

## Các bài tập về đồng dư thức

[Hackerearth - The Magical Shop](https://www.hackerearth.com/problem/algorithm/the-magical-shop/)

[Hackerearth - Chandu and his Interns](https://www.hackerearth.com/problem/algorithm/chandu-and-his-interns/)

[Hackerearth - The Confused Monk](https://www.hackerearth.com/problem/algorithm/the-confused-monk/)