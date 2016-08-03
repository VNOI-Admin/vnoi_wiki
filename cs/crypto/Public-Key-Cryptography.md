Bài viết này nhằm giúp bạn đọc nắm được ý tưởng cơ bản của các hệ mã hóa khóa công khai và một số ứng dụng của chúng. Ngoài ra, chúng ta cũng sẽ tìm hiểu về thuật toán mã hóa RSA, một hệ mã hóa khóa công khai được sử dụng khá phổ biến hiện nay.

[[_TOC_]]

# 1. Một số khái niệm

**Mã hóa** (Encryption): Quá trình chuyển đổi thông tin từ dạng thông thường, có thể tiếp nhận được sang thành dạng không tiếp nhận được (nếu không có khóa bí mật) nhằm mục đích giữ bí mật thông tin.

**Giải mã** (Decryption): Là quá trình ngược của mã hóa - chuyển đổi từ thông tin mã hóa về thông tin ban đầu.

**Khóa** (Key): Một đoạn thông tin được sử dụng để mã hóa, giải mã hoặc cả hai. 

# 2. Lịch sử

## 2.1. Mã hóa khóa đối xứng (Symmetric-key cryptography)

Cho đến trước năm 1976, các phương pháp mã hóa đều là mã hóa đối xứng. 

Các hệ mật mã đối xứng sử dụng chung khóa cho cả bên gửi lẫn bên nhận. Hai khóa này có thể giống nhau hoặc khác nhau nhưng có thể dễ dàng tìm ra được khóa còn lại nếu đã biết một khóa.

Ưu điểm của các phương pháp này là đơn giản, tốc độ cao, mang lại hiệu quả tốt nếu bạn không chia sẻ khóa của mình cho người khác. Tuy nhiên, chúng lại có các nhược điểm sau:

- Để có thể trao đổi thông tin bí mật với nhau, hai bên phải thống nhất với nhau trước về khóa bí mật. Bài toán đặt ra là làm sao có thể đảm bảo việc gửi khóa cho nhau là bí mật.
- Để đảm bảo trong 1 nhóm $n$ người cần phải có 1 số lượng khóa khá lớn - $\frac{n(n-1)}{2}$ khóa. Điều này dẫn đến một bài toán về việc lưu trữ, phân phối một số lượng lớn khóa mà vẫn phải đảm bảo sự an toàn của chúng.
- Do bên gửi và nhận sử dụng chung khóa, chúng ta không thể xác định được nguồn gốc của một thông điệp (message).

## 2.2. Mã hóa khóa công khai (Public-key cryptography)

Vào năm 1874, William Stanley Jevons viết trong quyển _The Principles of Science_ về mối liên hệ giữa các hàm một chiều và mật mã học. Đặc biệt, ông đã đi sâu vào bài toán phân tích ra thừa số nguyên tố (sau này được sử dụng trong thuật toán RSA). 

> _Liệu rằng bạn đọc có thể đoán được 2 số nguyên nào có tích bằng 8616460799? Tôi nghĩ rằng ngoài tôi ra thì không ai có thể biết kết quả được._

Năm 1976, Whitfield Diffie và Martin Hellman công bố bài báo [New Directions in Cryptography](http://www-ee.stanford.edu/~hellman/publications/24.pdf), làm thay đổi căn bản về cách các hệ mật mã hoạt động.  Bài báo đã đưa ra một hệ thống mã hóa bất đối xứng trong đó nêu ra phương pháp trao đổi khóa công khai, giải quyết các hạn chế của mã đối xứng.

Khác với mã đối xứng, mã hóa khóa bất đối xứng sử dụng một cặp khóa: khóa công khai (public key) và khóa bí mật (private key). Hai khóa này được xây dựng sao cho từ một khóa, rất khó có cách sinh ra được khóa còn lại. Một khóa sẽ dành để mã hóa, khóa còn lại dùng để giải mã. Chỉ có người sở hữu nắm được khóa bí mật trong khi khóa công khai được phổ biến rộng rãi. 

# 3. Ứng dụng

Mật mã hóa khóa công khai hay còn gọi là mã hóa bất đối xứng có 2 ứng dụng phổ biến sau:

## 3.3. Mã hóa công khai (_Public-key encryption_): 

Một thông điệp được mã hóa bằng khóa công khai của người nhận. Thông điệp này chỉ có thể giải mã được bằng khóa bí mật mà chỉ người nhận có. 

## 3.4. Chữ ký điện tử (_Digital signatures_): 

Chữ ký điện tử là thông tin đi kèm với dữ liệu nhằm mục đích xác định chủ sở hữu của dữ liệu đó.

Một văn bản được _"ký"_ bằng khóa bí mật của người gửi và có thể được xác nhận bới bất kỳ ai có khóa công khai của người gửi.

Cụ thể hơn, bên gửi sẽ tính ra mã hash $h$ của văn bản, sau đó dùng khóa bí mật để mã hóa $h$ thành $\sigma$ rồi gửi cho bên nhận văn bản đó cùng với _"chữ ký"_ $\sigma$ . Bên nhận thực hiện xác nhận như sau:

- Tính mã hash $h$ của văn bản.
- Giải mã _"chữ ký"_ $\sigma$ thành $h'$ bằng khóa công khai.
- So sánh $h$ và $h'$, nếu chúng bằng nhau thì quá trình xác thực thành công, ngược lại quá trình xác thực thất bại.

# 4. RSA

RSA là một trong những phương pháp mã hóa khóa công khai đầu tiên được ứng dụng rộng rãi trong việc đảm bảo an toàn khi truyền thông tin. Sự bất đối xứng của hệ mã này được dựa trên quan sát là khó có thể phân tích ra thừa số nguyên tố của một số là tích của 2 số nguyên tố. RSA được tạo thành bằng chữ cái đầu tiên của Ron Rivest, Adi Shamir, Lenonard Adleman, 3 người đầu tiên mô tả thuật toán vào năm 1977.

Nguyên lý cơ bản của RSA dựa trên nhận định là có thể tìm được 3 số nguyên dương rất lớn $e$, $d$ và $n$ mà:

$(m^e)^d \equiv m \pmod n \quad \forall m$

và dù cho có biết cả $e$, $d$ hay cả $m$ thì cũng rất khó để tìm ra $d$.

Tiếp theo chúng ta sẽ đi sâu vào từng công đoạn của 1 hệ mã, bao gồm việc mã hóa, giải mã và sinh khóa.

## 4.1 Mã hóa

Giả sử rằng Bob muốn gửi mẫu tin $M$ cho Alice.

Đầu tiên thông điệp $M$ thành từng phần nhỏ, mỗi phần biểu diễn bởi một số nguyên $m$ sao cho $0 \leq m < n$. Việc chuyển đổi này cần đảm bảo là ngẫu nhiên và $m$ không nhận các giá trị không an toàn (ví dụ như số 0 hay 1) nhưng vẫn đảm bảo là có thể suy ra $M$ từ $m$. Tiếp theo, Bob tính ra bản mã hóa $c$, sử dụng khóa công khai $e$ của Alice như sau:

$ c \equiv m^e \pmod n $

Bob gửi $c$ cho Alice.

Lưu ý rằng sao khi mã hóa, chính Bob cũng không thể giải mã được từ $c$ thành $m$.

## 4.2. Giải mã

Alice tính lại ra $m$ từ $c$ dựa vào khóa bí mật $d$:

$ c^d \equiv (m^e)^d \equiv m \pmod n $

Dựa vào $m$, Alice có thể khôi phục lại mẫu tin ban đầu $M$.

## 4.3. Sinh khóa (Key generation)

- Chọn 2 số nguyên tố khác nhau $p$ và $q$.

- Tính $n = p * q$. Độ dài của $n$ (tính theo bit) chính là độ dài của khóa. Hiện nay người ta khuyến cáo sử dụng khóa có độ dài tối thiếu 2048 bit.

- Tính $\varphi(n) = \varphi(p)\varphi(q) = (p - 1)(q - 1) = n - (p + q - 1)$. Trong đó $\varphi(n)$ là phi hàm Euler. $\varphi(n) =$ số lượng số nguyên dương nhỏ hơn $n$ mà nguyên tố cùng nhau với $n$.

- Chọn một số nguyên $e$ thỏa mãn $1 < e < \varphi(n)$ và $gcd(e, \varphi(n)) = 1$.

- Tính ra $d \equiv e^{-1} \pmod{\varphi(n)}$.

**Chứng minh**

Để chứng minh tính đúng đắn của thuật toán sinh khóa trên, ta cần chứng minh rằng $m^{ed} \equiv m \pmod n$ với $n = pq$.

**_1. Trường hợp $gcd(n, m) = 1$_**

Ta có $ed \equiv 1 \pmod{\varphi(n)}$

Do $e$ và $d$ nguyên dương nên $ed = 1 + h\varphi(n)$ với $h$ là một số nguyên không âm.

Do đó $m^{ed} = m^{1 + h\varphi{n}} = m(m^{\varphi(n)})^h$.

Theo định lý Euler, $a^{\varphi(n)} \equiv 1 \pmod n \quad \forall a, n: gcd(a, n) = 1$ nên $m(m^{\varphi(n)})^h \equiv m(1)^h \equiv m \pmod n$.

**_2. Trường hợp $gcd(n, m) \neq 1$_**

Theo định lý phần dư Trung Hoa (Chinese Remainder Theorem), nếu $p$, $q$ nguyên tố cùng nhau thì:

$x \equiv y \pmod p \quad và  \quad x \equiv y \pmod q \Rightarrow x \equiv y \pmod {pq}$.

Do vậy ta cần chứng mình 2 mệnh đề sau:

- $m^{ed} \equiv m \pmod p$
- $m^{ed} \equiv m \pmod q$

Vì $gcd(m, n) \neq 1 \Rightarrow gcd(m, n) = p \quad hoặc \quad gcd(m, n) = q$.

Không mất tính tổng quát, giả sử $gcd(m, n) = p$. Ta có:

- $gcd(m, p) = p \\ \Rightarrow m \equiv 0 \pmod p \\ \Rightarrow m^{ed} \equiv 0 \equiv m \pmod p$

- $gcd(m, q) = 1 \\ \Rightarrow m^{ed} \equiv m \pmod q$ 
(chứng mình tương tự trong trường hợp 1)


## 4.4. Sample code

```python
#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random

def is_prime(n):
    return all([(n % j) for j in range(2, int(n ** 0.5) + 1)]) and n > 1

# Sinh ra số nguyên tố ngẫu nhiên trong [left, right) mà khác exclude
def random_prime(left, right, exclude = -1):
    p = random.randint(left, right - 1);
    if is_prime(p) and p != exclude:
        return p
    else:
        return random_prime(left, right - 1, exclude)

# Thuật toán tìm nghịch đảo modulo
# MMI(A, n) = x thỏa mãn (Ax) mod n = 1
MMI = lambda A, n,s=1,t=0,N=0: (n < 2 and t%N or MMI(n, A%n, t, s-A/n*t, N or n),-1)[n<1]

# Thuật toán sinh khóa
def rsa_generate():
    p = random_prime(1, 255)
    q = random_prime(1, 255, p)
    n = p * q
    t = (p - 1) * (q - 1)
    e = random_prime(1, t)
    d = MMI(e, t)

    # Kết quả trả về bao gồm:
    #    - Khóa công khai (n, e)
    #    - Khóa bí mật (n, d)
    return n, e, d

def rsa_encrypt(message, n, e):
    return pow(message, e, n)

def rsa_decrypt(encrypt_message, n, d):
    return pow(encrypt_message, d, n)


# Example
n, e, d = rsa_generate()

print 'n={0}, e={1}, d={2}'.format(n, e, d)

message = random.randint(1, n - 1)
print 'Original message: {0}'.format(message)

encrypted_message = rsa_encrypt(message, n, e)
print 'Encrypted message: {0}'.format(encrypted_message)

decrypted_message = rsa_decrypt(encrypted_message, n, d)
print 'Decrypted message: {0}'.format(decrypted_message)
```

# 5. Tham khảo

[Wiki - Public-key Cryptography](https://en.wikipedia.org/wiki/Public-key_cryptography)

[Wiki - RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem))
 
[Wiki - History of Cryptography](https://en.wikipedia.org/wiki/History_of_cryptography)