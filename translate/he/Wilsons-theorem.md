# Định lý Wilson

# Định lý

Số tự nhiên $n>1$ là số nguyên tố khi và chỉ khi $(n-1)!\equiv n-1 (mod \ n)$.

# Ví dụ

- Với $n=4$:

	$(n-1)!\ =6$

	$(n-1)!\ mod\ n\ =2$

- Với $n=5$:

	$(n-1)!\ =24$

	$(n-1)!\ mod\ n\ =4$

- Với $n=6$:

	$(n-1)!\ =120$

	$(n-1)!\ mod\ n\ =0$

- Với $n=11$:

	$(n-1)!\ =3628800$

	$(n-1)!\ mod\ n\ =10$

- Với $n=12$:

	$(n-1)!\ =39916800$

	$(n-1)!\ mod\ n\ =0$

# Chứng minh

Mệnh đề đúng với $n=2$ và $n=3$. Ta giả sử $n>3$:

- $n$ là hợp số

	$\Leftrightarrow$ tồn tại ước của $n$ trong khoảng $(1;n)$

	$\Leftrightarrow \ gcd((n-1)!,n)>1$ do $(n-1)!=1.2.3...(n-1)$

	$\Leftrightarrow \ gcd((n-1)! \ mod \ n,n)>1$

	Nếu $(n-1)! \ mod \ n \ = n-1$ thì $gcd((n-1)! \ mod \ n,n)=gcd(n-1,n)=1$ (vô lý).

- Nếu $n$ là số nguyên tố thì $gcd(a,n)=1$ với mọi $a$ tự nhiên nhỏ hơn $n$, và theo lý thuyết số thì luôn tồn tại số $b$ duy nhất sao cho $ab \ mod \ n \ =1$, mặt khác $a=b$ khi và chỉ khi $a=1$ hoặc $a=n-1$ nên ta có:

	$2.3.4...(n-2) \ mod \ n =1 \ \Rightarrow \ 1.2.3..(n-1)=(n-1)! \ mod \ n = n-1$

# Luyện tập

- [[https://www.hackerearth.com/problem/algorithm/factorial-again-1/]]