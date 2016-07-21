#Toán học cho <strong> Topcoder </strong>

---
 
## Giới thiệu:

 <p style="text-align: justify;">      Tôi đã từng thấy nhiều người thi <strong> Topcoder </strong> phàn nàn việc thiếu công bằng trong đề thi, khi mà có quá nhiều thứ thuộc về Toán học – điểm yếu của họ. Cá nhân tôi, tôi yêu Toán và vì vậy mà tôi sẽ có phần thiên vị hơn trong vấn đề này. Tuy nhiên, tôi hoàn toàn tin tưởng rằng, cái bài tập nên có <strong>ít nhất một thứ thuộc về Toán học và Khoa học máy tính phải đi liền với nó</strong>. Thật khó tưởng tượng khi mà cả hai lĩnh vực này cũng tồn tại mà không hề có bất kỳ sự tương tác nào lẫn nhau. Ngày nay, một trong những sự kết hợp tuyệt vời đó chính là việc áp dụng Toán học vào Tin học bằng việc giải những hệ thống phương trình to lớn hay tìm nghiệm xấp xỉ đối với những phương trình mà không hề tồn tại một công thức nào cả. Toán học còn được sử dụng rộng rãi trong việc nghiên cứu về <i>Khoa học máy tính</i>, cũng như là áp dụng cho các <i>thuật toán về đồ thị</i> và <i>lĩnh vực thị giác máy tính</i>. </p>

 <p style="text-align: justify;"> <i>Bài viết này sẽ thảo luận về lý thuyết và ứng dụng của một vài cấu trúc Toán học phổ biến</i>. Các chủ đề được đề cập tới bao gồm: </p>

1.        Số nguyên tố.<br>
2. 	  Ước chung lớn nhất <i>(GCD)</i>.<br>
3. 	  Hình học cơ bản.<br>
4. 	  Hệ cơ số.<br>
5. 	  Phân số và số phức.<br>


## Số nguyên tố:

 <p style="text-align: justify;"> Một số tự nhiên là số nguyên tố <i> khi và chỉ khi nó chỉ chia hết cho 1 và chính nó</i>. Ví dụ như 2, 3, 5, 79, 311 và 1931 đều là số nguyên tố, trong khi 21 thì không phải, bởi nó chia hết cho 3 và 7. Để xác định xem một số tự nhiên n có phải là số nguyên tố hay không, ta chỉ cần đơn giản kiểm tra xem nó có chia hết cho bất kỳ số nào nhỏ hơn nó và lớn 1 hay không. Chúng ta có thể sử dụng phép chia có dư (toán tử %) để kiểm tra <strong>khả năng chia hết của nó</strong>: </p>
C++

```
    for (int i = 2; i < n; i++) 
        if (n%i == 0) return false;

    return true;

```

pascal

```
	for i := 2 to n - 1 do
		if (n mod i = 0) then exit(false);

	exit(true);
```
 <p style="text-align: justify;"> Chúng ta còn có thể làm cho đoạn mã này chạy nhanh hơn nữa bằng việc nhận ra rằng, ta chỉ cần xét khả năng chia hết cho <i>mọi giá trị i lớn hơn 1 và nhỏ hơn hoặc bằng với phần nguyên của căn bậc 2 của n </i>, <strong>tạm gọi là m</strong>. Tại sao lại thế nhỉ ? Đấy là bởi vì nếu n chia hết cho bất kỳ số n lớn hơn m thì kết quả nhận được cũng chỉ là một số nhỏ hơn hoặc bằng m. Tiếp tục cải tiến, ta sẽ thấy rằng <strong>không tồn tại</strong> <i>bất kỳ một số nguyên tố chẵn nào lớn hơn 2</i>. Và giờ, sau khi đã kiểm tra rằng n là số lẻ thì ta có thể an tâm tăng biến <i>i</i> lên 2 giá trị. Đây sẽ là đoạn mã áp dụng phương thức kiểm tra số nguyên tố mới nhất này:</p>

C++

```
    public boolean isPrime (int n)
    {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n%2 == 0) return false;
        int m = Math.sqrt(n);
	
        for (int i = 3; i <= m; i += 2)
            if (n%i == 0)
                return false;
		
        return true;
    }
```

pascal

```
	function IsPrime (n : Integer): Boolean;
	var
		i : Integer;
		m : Integer;
	begin
		if (n <= 1) exit(false);
		if (n = 2) exit(true);
		if (n mod 2 = 0) exit(false);
		i := 3;
		m := trunc(sqrt(n));
		while (i <= m) do
			begin
				if (n mod i = 0) exit(false);
				inc(i, 2);
			end;
		exit(true);
	end;
```
 <p style="text-align: justify;"> Giả định rằng chúng ta cần phải tìm mọi số nguyên tố trong khoảng <strong>[1, 100000]</strong>, thì chẳng lẽ ta phải gọi hàm kiểm tra <strong>100000</strong> lần sao ? Việc lặp đi lặp lại các phép kiểm tra tương tự thật sự không hiệu quả chút nào. Trong tình huống này, phương pháp tối ưu nhất chính là sử dụng <strong>Sàng nguyên tố Eratosthenes</strong>. <i>Sàng nguyên tố <strong>Eratosthenes</strong></i> sẽ xác định toàn bộ những số nguyên tố trong khoảng <strong>[2, n]</strong>. Trước hết, sàng nguyên tố sẽ giả định mọi số tự nhiên từ <i>2</i> đến <i>n</i> là số nguyên tố. Kế đến, nó sẽ chọn ra số nguyên tố đầu tiên và <strong>xóa đi những bội nhỏ hơn bằng <i>n</i></strong> của số nguyên tố đó. Và nó lại tiếp tục quá trình bằng lựa một số nguyên tố tiếp theo và xóa đi các bội của nó. Quá trình này sẽ tiếp tục diễn ra cho đến khi mà mọi số đều đã xử lý. Ví dụ, ta sẽ tìm các số nguyên tố trong khoảng <strong>[2, 20]</strong>. Trước hết, ta hãy ghi ra dãy số đó: </p>
```
    2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
```
 <p style="text-align: justify;"> Bởi vì 2 là số nguyên tố đầu tiên, nên ta sẽ loại bỏ đi tất cả những bội của 2 và nhỏ hơn bằng 20.</p>
```	
    2 3 5 7 9 11 13 15 17 19
```
 <p style="text-align: justify;"> Bởi vì 3 là số đầu tiên chưa bị bỏ, nên ta sẽ lựa chọn 3 là số nguyên tố tiếp theo và loại bỏ đi tất cả những bội của 3 và nhỏ hơn bằng 20.</p>
```
    2 3 5 7 11 13 17 19
```
 <p style="text-align: justify;"> Tiếp đến, ta sẽ chọn 5, ta thấy không còn bội nào của 5 nhỏ hơn bằng 20 còn sót nên ta lại tiếp tục xét đến 7, ...</p>
 <p style="text-align: justify;"> Và giờ thì tất cả những số còn sót lại chính là các số nguyên tố mà ta cần tìm. Dưới đây là đoạn mã cho <strong>Sàng nguyên tố Eratosthenes:</strong></p>

C++

```
    public boolean[] sieve(int n)
    {
        boolean[] prime=new boolean[n+1];
        Arrays.fill(prime,true);
        prime[0]=false;
        prime[1]=false;
        int m=Math.sqrt(n);
		
        for (int i=2; i<=m; i++)
            if (prime[i])
                for (int k=i*i; k<=n; k+=i)
                    prime[k]=false;
		
        return prime;
    } 
```

pascal

```
	//mảng kiểm tra số nguyên tố prime[0..n]

	function sieve(n : Integer): Boolean;	
	var
		i, m : Integer;
	begin
		fillchar(prime, sizeof(prime), 1);
		prime[0] := false;
		prime[1] := false;
		for i := 2 to m do
			if (prime[i]) then
				for j := i to n div i do
					prime[i * j] := false;
	end;
```
 <p style="text-align: justify;"> Ở đoạn mã trên, ta sẽ tạo một mảng <i>prime</i>, nơi sẽ chứa các giá trị nguyên trong khoảng <strong>[0, n]</strong>. <i>Prime[i]</i> là <strong>true</strong> nếu i là số nguyên tố và ngược lại. Vòng lặp bên ngoài sẽ tìm kiếm số nguyên tố tiếp theo, trong khi vòng lặp bên trong sẽ loại bỏ đi tất cả những bội nhỏ hơn bằng <i>n</i> của số nguyên tố đó.</p>

## Ước chung lớn nhất

<p style="text-align: justify;"><strong>Ước chung lớn nhất <i>(GCD)</i></strong> của hai số  tự nhiên <i>a</i> và <i>b</i> là <strong>số lớn nhất mà cả <i>a</i> và <i>b</i> đều chia hết</strong>. Để tìm được <i>GCD(a, b)</i>, một cách đơn giản, ta có thể lấy số nhỏ hơn trong hai số <i>a</i> và <i>b</i> rồi <i>giảm dần</i> cho đến khi nào có được một số mà cả <i>a</i> và <i>b</i> đều <i>cùng chia hết</i> cho số đó.</p>

C++

```
    for (int i=Math.min(a,b); i>=1; i--)
        if (a%i==0 && b%i==0)
            return i;
```

pascal

```
	for i := min(a, b) downto 1 do
		if (a mod i = 0) and (b mod i = 0) then exit(i);
```
 <p style="text-align: justify;"> Mặc dù phương pháp này đủ nhanh để đáp ứng phần lớn các trường hợp, song ta vẫn còn một cách nhanh hơn nữa, đó chính là <strong>thuật toán Euclid</strong>. Thuật toán <i> Euclid</i> sẽ lặp đi lặp lại việc xử lý hai số cho đến khi mà phần dư của chúng bằng 0. Ví dụ, giả sử chúng ta muốn tìm ước chung lớn nhất của hai số 2336 và 1314. Đầu tiên, ta sẽ phân tích số lớn hơn là 2336 thành bội của 1314 cộng thêm cho phần dư.</p>
```
    2336 = 1314 x 1 + 1022
```
 <p style="text-align: justify;"> Ta sẽ thực hiện tương tự với 1314 và 1022.</p>
```
    1314 = 1022 x 1 + 292
```
 <p style="text-align: justify;"> Ta tiếp tục quá trình cho đến khi phần dư bằng 0.</p>
```
    1022 = 292 x 3 + 146
    292 = 146 x 2 + 0
```
 <p style="text-align: justify;"> Và phần dư cuối cùng mà khác 0 chính là ước chung lớn nhất mà ta cần tìm. Vậy ước chung lớn nhất của 1314 và 2336 chính là 146. Thuật toán trên sẽ được mô phỏng lại bằng một đoạn mã đệ quy đơn giản:</p>

C++

```
    //giả định rằng a và b đều khác 0
    public int GCD(int a, int b)
    {
        if (b==0) return a;
        return GCD(b,a%b);
    }

	//bạn cũng có thể sử dụng hàm __gcd(a, b) ở thư viện algorithm

```	

pascal

```
	//giả định a và b đều khác 0
	function GCD(a, b : Integer): Integer;
	begin
		if (b = 0) then exit(a)
		else exit(GCD(b, a mod b));
	end;
```
 <p style="text-align: justify;"> Đặc biệt, <strong>thuật toán Euclid</strong> còn được áp dụng trong việc tìm <i>bội chung nhỏ nhất (LCM)</i> của hai số tự nhiên. Ví dụ, bội chung nhỏ nhất của 6 và 9 là 18 vì 18 là số nhỏ nhất mà <i>chia hết cho cả a lẫn b</i>. Dưới đây là đoạn mã cho việc tìm bội chung nhỏ nhất:</p>

C++

```
    public int LCM(int a, int b)
    {
        return b*a/GCD(a,b);
    }

```

pascal

```
	function LCM(a, b : Integer): Integer;
	begin
		exit(a * b / GCD(a, b));
	end;
```
 <p style="text-align: justify;"> Một chú ý cuối cùng đó là việc <strong>thuật toán Euclid</strong> còn có thể dùng để giải <strong>phương trình tìm nghiệm nguyên Diophantine</strong>. Đó là những phương trình có <i>hệ số và ẩn số nguyên (a, b, c, x, y ∈ N)</i> và được biểu diễn như sau:</p>
```
    ax + by = c
```
 Xem thêm: [Thuật toán Euclid mở rộng](http://vnoi.info/library/82/419/)

## Hình học

 Đôi khi, bài toán yêu cầu ta tìm phần giao của các hình chữ nhật. Có rất nhiều cách để biểu diễn một hình chữ nhật. Đối với hệ trục tọa độ <i>Cartesian</i>, thì cách biểu diễn phổ biến nhất chính là lưu giữ giá trị tọa độ của góc <strong>trái - dưới</strong> và góc <strong>phải - trên</strong> của hình chữ nhật.
<br>
 Giả sử chúng ta có hai hình chữ nhật R1 và R2. Đặt <i>(x1, y1)</i> là tọa độ góc trái - dưới, <i>(x2, y2)</i> là tọa độ góc phải - trên của hình chữ nhật R1. Tương tự với R2, ta đặt <i>(x3, y3)</i>, <i> (x4, y4)</i> lần lượt là tọa độ góc trái - dưới và góc phải - trên của R2. Phần giao của R1 và R2 sẽ là hình chữ nhật R3 có tọa độ trái - dưới là <i><strong>(max(x1, x3), max(y1, y3))</strong></i> và tọa độ góc phải - trên là <i><strong>(min(x2, x4), min(y2, y4))</strong></i>. Nếu <strong> max(x1, x3) > min(x2, x4)</strong> hoặc <strong>max(y1, y3) > min(y2, y4)</strong> thì sẽ <i>không tồn tại</i> hình chữ nhật R3, hay nói các khác là R1 và R2 không giao nhau. Công thức này còn được mở rộng ra hơn không gian 2 chiều giống như là trong bài [<i>CuboidJoin (SRM 191, Div 2 Hard)</i>](http://topcoder.bgcoder.com/print.php?id=514). 
<br>
 Thường thì, khi làm bài chúng ta sẽ phải đối mặt với những đa giác mà cạnh của nó mang giá trị nguyên. Những đa giác đó được gọi là [<strong>Đa giác lưới</strong>](http://mathworld.wolfram.com/LatticePolygon.html). Trong phần <i>hướng dẫn cơ bản về khái niệm hình học</i> ([<strong>Geometry Concepts</strong>](https://www.topcoder.com/community/data-science/data-science-tutorials/geometry-concepts-basic-concepts/)), lbackstrom đã trình bày một cách ngắn gọn cách tính diện tích thông qua các cạnh của đa giác. Bây giờ, giả sử ta không biết được chính xác vị trí các cạnh mà thay vào đó ta có được các giá trị sau:
```
    B = số lượng điểm nằm ở rìa đa giác
    I = số lượng điểm nằm trong đa giác
```
 <p style="text-align: justify;"> Thật kỳ diệu, thông qua hai giá trị trên ta có thể tính được diện tích đa giác bằng công thức sau:</p>
```
    Diện tích = B/2 + I - 1
```
Công thức trên được gọi là [<strong>định lý Pick</strong>](https://en.wikipedia.org/wiki/Pick%27s_theorem) được chứng minh bởi <i>Georg Alexander Pick (1859 – 1943)</i>. Để chứng minh được rằng <i>định lý Pick</i> có tính chất bao quát cho toàn bộ mọi đa giác lưới, ta sẽ chứng minh lần lượt 4 phần riêng rẽ sau. <strong>Phần 1</strong>, ta cần chứng minh <i>định lý Pick đúng với mọi hình chữ nhật lưới, có cạnh song song với trục tọa độ</i>. <strong>Phần 2</strong>, không khó để ta chứng minh được định lý Pick vẫn đúng với mọi tam giác vuông có hai cạnh song song với trục tọa đô (<i>bởi chúng là phân nửa diện tích một hình chữ nhật lưới có tọa độ một đỉnh là góc vuông của tam giác và có cạnh là các cạnh góc vuông của tam giác</i>). <strong>Phần 3</strong>, ta sẽ tiếp tục chứng minh <i>định lý Pick đúng với mọi tam giác</i>, bởi một tam giác bất kỳ đều có thể biểu diễn thành một hình chữ nhật bằng cách ghép cặp với một vài tam giác vuông khác. <strong>Phần 4</strong>, ta thấy rằng mọi đa giác lưới có chung cạnh sẽ tạo thành một đa giác lưới khác bằng cách xóa đi cạnh chung, và <i>mọi đa giác lưới đều có thể tạo ra bằng cách ghép các hình chữ nhật và tam giác</i>. Tổng hợp lại 4 phần trên và ta sẽ thu được kết quả rằng <strong>định lý Pick đúng với mọi đa giác lưới</strong>. <i>Định lý Pick</i> khá hữu ích khi ta cần tìm số điểm có tọa độ nguyên bên trong một đa giác lớn.
<br>
 Một công thức đáng nhớ khác đó chính là công thức [Euler](https://en.wikipedia.org/wiki/Euler%27s_formula) dành cho các <strong>khối đa diện</strong>. Khối đa diện được định nghĩa là một khối (một đa giác) mà ta có thể chia thành nhiều đa giác nhỏ hơn. Các đa giác nhỏ hơn được gọi là <i>mặt</i>, cách đỉnh của mặt cũng được gọi là <i>đỉnh</i> của khối đa diện và tương tự, các cạnh của mặt cũng gọi là <i>cạnh</i>. Dưới đây là công thức <strong>Euler</strong>.
```
    V - E + F = 2, với:
        V = số cạnh của khối
        E = số đỉnh của khối
        F = số mặt của khối
```
Ví dụ, xét một hình vuông mà cả hai đường chéo đều được vẽ. Ta sẽ có V = 5, E = 8 và F = 5 (phần nằm ngoài hình vuông cũng được coi như là một mặt), ta sẽ có <i>V - E + F = 2</i>.<br>
Ta có thể sử dụng quy nạp để chứng minh nó như sau: Ta sẽ bắt đầu với V = 2, vì mỗi đỉnh đều cần phải có ít nhất một cạnh. Và nếu V = 2 thì chỉ có xảy ra duy nhất một dạng khối đa diện mà thôi. Đó là dạng khối đa diện mà hai cạnh sẽ nối với E đỉnh. Khối đa diện nãy cũng sẽ có E mặt, (E-1 mặt bên trong hình và 1 mặt ngoài hình). Thế nên <strong>V - E + F = 2 - E + E = 2</strong> (<i>điều phải chứng minh</i>). Giờ ta giả sử định lý Euler đúng với V từ <strong>[2, n]</strong>, xét <i>V = n+1</i>. Chọn một cạnh <i>w</i> bất kỳ. Giờ giả định <i>w</i> nối với tất cả những lưới còn lại có G đỉnh. Nếu bỏ đi cạnh <i>w</i> này và những đỉnh mà nó nối, ta sẽ có một lưới với <i>n</i> cạnh, <i>E - G</i> đỉnh và <i>F-G+1</i> mặt. Từ giả định trên ta có:
```
    (n) - (E - G) + (F - G + 1) = 2
    <=> (n+1) - E + F = 2
```
Vậy với V = n+1, ta cũng vẫn thu được kết quả là V - E + F = 2. Vậy là với phương pháp quy nạp toán học, ta đã chứng minh được định lý Euler.

## Hệ cơ số:

 Một trong những bài toán mà người thi <strong>Topcoder</strong> đối mặt nhiều nhất đó chính là việc chuyển đổi số từ <i>hệ cơ số nhị phân</i> sang <i>hệ cơ số thập phân</i> và ngược lại (cùng với nhiều hệ cơ số khác).<br>
Vậy hệ cơ số nghĩa là gì ? Ta sẽ bắt đầu với hệ cơ số tiêu chuẩn (<i>hệ thập phân</i>). Xét số 4325 ở hệ cơ số 10. Ta thấy 4325 có thể phân tích thành <i>5 + 2 x 10 + 3 x 10 x 10 + 4 x 10 x 10 x 10</i>. Chú ý rằng mỗi <i>"giá trị"</i> của chữ số tiếp theo sau của số được nhân thêm tích số 10 khi ta xét từ phải qua trái. <strong>Hệ nhị phân</strong> cũng hoạt động theo cách tương tự như thế. Nó sử dụng hai chữ số 0 và 1 và <i>"giá trị"</i> của từng chữ số sẽ được nhân thêm 2 khi ta xét từ phải qua trái. Ví dụ, số 1011 ở dạng nhị phân có thể biểu diễn thành <i>1 + 1 x 2 + 0 x 2 x 2 + 1 x 2 x 2 x 2 = 1 + 2 + 8 = 11</i> và trở lại thành số ở hệ thập phân là 11. Và đây chính là cách để ta chuyển từ số ở hệ nhị phân (<i>hoặc bất kỳ hệ số nào</i>) về hệ cơ số thập phân. Sau đây là đoạn mã để chuyển từ một hệ cơ số n (<i>2 <= n <= 10</i>) thành hệ cơ số thập phân.

C++

```
    public int toDecimal(int n, int b)
    {
        int result = 0;
        int multiplier = 1;
		      
        while(n > 0)
        {
            result += n%10*multiplier;
            multiplier *= b;
            n /= 10;
        }
      
        return result;
    }
```

pascal

```
    function ToDectimal(n, b : Integer): Integer;
    var
        mul : Integer = 1;

    begin
        result := 0;

        while (n > 0) do
            begin
                result := result + (n mod 10) * mul;
                mul := mul * b;
                n := n div 10;
            end;
    end;
```

 Người dùng <strong>Java</strong> hẳn sẽ rất vui khi biết rằng vẫn có cách khác đơn giản hơn để thực hiện việc này.
```	
    return Integer.parseInt(""+n,b);
```
 Để chuyển một số từ hệ thập phần về hệ nhị phân cũng khá đơn giản. Giả sử ta muốn chuyển số 43 từ hệ thập phân về hệ nhị phân. Tại bước đầu của công thức ta sẽ chia đôi 43 và lưu lại giá trị phần dư, tiếp tục xử lý với số được chia đôi đó cho đến khi nó bằng 0. Và danh sách số dư sau cuối cùng cũng chính là cách biểu diễn số nhị phân cần tìm.
```
    43/2 = 21 + dư 1
    21/2 = 10 + dư 1
    10/2 = 5  + dư 0
    5/2  = 2  + dư 1
    2/2  = 1  + dư 0
    1/2  = 0  + dư 1
```
  Vậy 43 sẽ được biểu diễn thành 101011 ở dạng nhị phân. Bằng việc thay số 2 thành số <i>b</i>, ta có thể chuyển từ hệ thập phân về bất kỳ hệ cơ số <i>b</i> nào (<i>2 <= b <= 10</i>):

C++

```
    public int fromDecimal(int n, int b)
    {
        int result = 0;
        int multiplier = 1;
	      
        while(n > 0)
        {
            result += n%b*multiplier;
            multiplier *= 10;
            n /= b;
        }
		      
        return result;
    }
```

pascal

```
    function FromDecimal(n, b : Integer): Integer;
    var
        mul := 1;
    begin
        result := 0;

        while (n > 0) do
            begin
                result := result + (n mod b) * mul;
                mul := mul * 10;
                n := n div b;
            end;
    end;
```
 Đối với trường hợp <i>b</i> lớn hơn 10, ta sẽ xử dụng các ký tự không phải số để đại diện cho các số từ 9 trở lên. Ví dụ, ta sẽ để <i>'A'</i> đại diện cho 10, <i>'B'</i> cho 11, ... Đoạn mã sau đây sẽ cho phép ta chuyển từ số thập phân sang bất kỳ hệ cơ số nào (lên đến 20).

C++

```
    public String fromDecimal2(int n, int b)
    {
        String chars = "0123456789ABCDEFGHIJ";
        String result = "";
	      
        while(n > 0)
        {
            result = chars.charAt(n%b) + result;
            n /= b;
        }
		      
        return result;
    }
```

pascal

```
    function FromDecimal2(n, b : Integer): String;
    var
        chars : string = '0123456789ABCDEFGHIJ';
    begin
        result := '';

        while (n > 0) do
            begin
                result := chars[n mod b + 1] + result;
                n := n div b;
            end;
    end;
```
 Trong <strong>Java</strong>, ta có thể sử dụng những cách tắt sau để chuẩn từ hệ thập phân sang như hệ số thông dụng khác, như là hệ nhị phân, hệ bát phân, hệ thập lục phân.
```
    Integer.toBinaryString(n);
    Integer.toOctalString(n);
    Integer.toHexString(n);
```

## Phân số và số phức

 Phân số thường được gặp rất nhiều trong các bài tập. Thường thì vấn đề khó khăn nhất mà ta cần phải đối mặt đó chính là việc biểu diễn các phân số đó. Mặc dù nó hoàn toàn khả thi trong việc tạo ra một lớp (<i>class</i>) khác để lưu trữ một cách đầy đủ các thông tin về phần số, nhưng trong nhiều trường hợp thì cách thường dùng nhất là sử dụng mảng lưu 2 giá trị bằng cách ghép cặp (<i>pair</i>). Ý tưởng là ta sẽ lưu số đầu tiên là <strong>tử số</strong>, số thứ hai là <strong>mẫu số</strong>.Ta sẽ bắt đầu bằng việc nhân hai phân số <i>a</i> và <i>b</i>:

C++

```
    public int[] multiplyFractions(int[] a, int[] b)
    {
        int[] c = {a[0]*b[0], a[1]*b[1]};
        return c;
    }
```

pascal

```
    type
        ps = record
        x, y : Integer;
        end;

    function multiplyFractions(a, b : ps): ps;
    var
        c : ps;
    begin
        c.x := a.x * b.x;
        c.y := a.y * b.y;
        exit(c);
    end;
```
 Cộng phân số thì có một chút phức tạp hơn, bởi chỉ có nhưng phân số có cùng mẫu số mới có thể cộng trực tiếp. Trước hết ta sẽ tìm <strong>mẫu số chung</strong> của hai phân số và nhân tử số hai phân số theo tỉ số giữa mẫu số cũ với mẫu số chung. <i>Mẫu số chung</i> là số có thể chia hết cho cả mẫu của hai phân số, hay đơn giản hơn đó chính là <i>bội chung nhỏ nhất</i> của hai mẫu số. Ví dụ để cộng hai phân số 4/9 và 1/6. <i>Bội chung nhỏ nhất</i> của 9 và 6 là 18. Để chuyển đổi hai phân số ta sẽ lấy phân số thứ nhất nhân cho 2/2 và số thứ hai cho 3/3.
```
    4/9 + 1/6 = (4*2)/(9 * 2) + (1 * 3)/(6 * 3) =  8/18 +  3/18
```
 Một khi hai phân số đã có mẫu số bằng nhau, thì ta chỉ cần đơn giản cộng hai phân số đó lại và nhận kết quả cuối cùng là phân số 11/18. Trừ cũng rất đơn giản, chỉ khác nhau ở bước cuối cùng.
```
    4/9 - 1/6 =  8/18 - 3/18 =  5/18
```

 Đây là đoạn mã cho chương trình công hai phân số: 

C++

```
    public int[] addFractions(int[] a, int[] b)
    {
        int denom = LCM(a[1],b[1]);
        int[] c= {denom/a[1]*a[0] + denom/b[1]*b[0], denom};
        return c;
    }
```

pascal

```
    function addFractions(a, b : ps): ps;
    var
        a, b : ps;
        denom : Integer;
    begin
        denom := LCM(a.y, b.y);
        result.x := denom div a.y * a.x + denom div b.y * b.x;
        result.y := denom;
    end;
```
  Cuối cùng, nó rất cần thiết để biết được cách <i>tối giản phân số</i> thành <strong>phân số tối giản</strong>. Và phân số chỉ tối giản khi và chỉ khi ước chung lớn nhất của tử số và mẫu số là 1. Chúng ta sẽ làm như sau:

```
    public void reduceFraction(int[] a)
    {
        int b = GCD(a[0],a[1]);
        a[0] /= b;
        a[1] /= b;
    }
```

 Bằng phương pháp tương tự, ta cũng có thể biểu diễn được số phức. Một cách tổng quát, số phức được biểu diễn dưới dạng <i>a + ib</i> với <i>a</i>, <i>b</i> là số thực và <i>i</i> là căn bậc hai của -1. Ví dụ, để cộng hai số phức, ta sẽ cộng đơn giản như sau:
```
    m + n
    = (a + ib) + (c + id)
    = (a + c) + i(b + d)
```
 Việc nhân hai số phức cũng tương tự như việc nhân số thực, trừ việc <i>i*i</i> bằng -1.

```
    m * n
    = (a + ib) * (c + id)
    = ac + iad + ibc + (i^2)bd
    = (ac - bd) + i(ad + bc)
```
  Bằng việc lưu trữ phần số thực ở phần tử thứ nhất và phần số phức ở phần tử thứ hai trong một mảng hai giá trị như đoạn mã dưới đây:

C++

```
    public int[] multiplyComplex(int[] m, int[] n)
    {
        int[] prod = {m[0]*n[0] - m[1]*n[1], m[0]*n[1] + m[1]*n[0]};
        return prod;
    }
```

pascal

```
    function multiplyComplex(m, n : ps): ps;
    begin
        result.x := m.x * n.x - m.y * n.y;
        result.y := m.x * n.y + m.y * n.x;
    end;
```

##  Tổng kết:
<br>

 Tổng kết lại, tôi chỉ muốn nói rằng đó là bất khả thi nếu bạn muốn đứng đầu <strong>Topcoder</strong> mà không hiểu chút gì về những cấu trúc Toán học và những thuật toán mà tôi vừa nêu lên. Thường thì một trong những chủ đề Toán học thường gặp nhất trong các bài tập đó là <strong>số nguyên tố</strong>. Nó cũng thường liên quan đến những bài về <strong>hệ cơ số</strong>, mà nguyên nhân chủ yếu là vì máy tính hoạt động dựa trên hệ nhị phân, nên ta cần phải biết cách chuyển từ hệ nhị phân về hệ thập phân. Còn công thức tính ước chung lớn nhất (<strong>GCD</strong>) và bội chung nhỏ nhất (<strong>LCM</strong>) thì được dùng nhiều trong cả những bài tập <i>"thuần toán"</i> và cả hình học. Cuối cùng, tôi viết chủ đề <strong>Phân số và số phức</strong> là việc nó không chỉ cần thiết cho việc thi <strong>Topcoder</strong>, mà bởi nó còn vô cùng quan trọng trong việc biểu diễn ý nghĩa các số nhất định.
