[[_TOC_]]
Nguồn bài: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/computational-complexity-section-2/)

[...đọc phần 1](http://vnoi.info/contributor/translate/topcoder/Computational-Complexity-Section-1)

# Giới thiệu
Trong phần này của bài viết chúng ta sẽ tập trung vào việc ước lượng độ phức tạp cho các chương trình đệ quy. Về mặt bản chất việc này sẽ dẫn tới khảo sát tốc độ tăng của các hàm độ phức tạp thời gian thỏa mãn các công thức truy hồi. Nếu bạn chưa hiểu chính xác thế nào là một thuật giải đệ quy thì không cần lo lắng vì nó sẽ được giải thích trong các phần sau. Trước mắt chúng ta sẽ xem xét trường hợp đơn giản hơn - các chương trình không sử dụng đệ quy.


# Vòng lặp lồng nhau

Để mở đầu, ta xét các chương trình đơn giản không sử dụng các lời gọi đệ quy. Với các chương trình như vậy, ba quy tắc phổ biến dễ áp dụng để tìm cận trên của độ phức tạp là:

+ Tính số lần lặp tối đa của một vòng lặp
+ Nếu các vòng lặp nối tiếp nhau thì **cộng** các cận đó với nhau
+ Nếu các vòng lặp lồng nhau thì **nhân** các cận với nhau

## Ví dụ 1
Ước lượng độ phức tạp của đoạn mã sau:
~~~cpp
int result=0;                           //  1
for (int i=0; i<N; i++)                 //  2
  for (int j=i; j<N; j++) {             //  3
    for (int k=0; k<M; k++) {           //  4
      int x=0;                          //  5
      while (x<N) { result++; x+=3; }   //  6
    }                                   //  7
    for (int k=0; k<2*M; k++)           //  8
      if (k%7 == 4) result++;           //  9
  }                                     // 10
~~~

Rõ ràng độ phức tạp của vòng lặp $while$ ở dòng 6 là $O(N)$ - số lần lặp không vượt quá $N/3+1$ lần.

Xét vòng lặp $for$ ở các dòng 4 - 7. Dễ thấy biến $k$ được tăng lên $M$ lần. Mỗi lần như vậy thì toàn bộ vòng lặp $while$ ở dòng 6 lại được thực thi. Như vậy tổng số độ phức tạp của đoạn lệnh từ dòng 4 tới 7 là $O(MN)$ (áp dụng quy tắc 3)

Độ phức tạp của vòng $for$ ở các dòng 8 - 9 là $O(M)$. Như vậy tổng độ phức tạp của dòng từ 4 tới 9 là $O(MN + M) = O(MN)$ (áp dụng quy tắc 2 và loại đại lượng không đáng kể)

Toàn bộ phần mã bên trong này được thực thi $O(N^2)$ lần - mỗi lần tương ứng với một tổ hợp của biến $i$ và $j$ (dòng 2 và 3) (chú ý là chỉ có $N(N + 1)/2$ giá trị khác nhau cho bộ số $[i,j]$. Mặc dù vậy $O(N^2)$ vẫn là cận trên đúng).

Từ nhận xét trên ta có tổng độ phức tạp của thuật toán trong Ví dụ 1 là $O(N^2 MN) = O(MN^3)$.

Từ ví dụ trên người đọc đã có khả năng phân tích độ phức tạp của các phần mã đơn giản sử dụng phương pháp như đã trình bày. Chúng ta sẽ đi tới xem xét các chương trình có sử dụng đệ quy (tức là một hàm số mà trong thân hàm của nó sẽ gọi tới chính nó với tham số khác) và phân tích ảnh hưởng của những lời gọi đệ quy này tới độ phức tạp của chúng.

# Sử dụng đệ quy để sinh các cấu hình tổ hợp

Một ứng dụng phổ biến của đệ quy là cài đặt thuật toán quay lui để sinh ra tất cả các nghiệm của một bài toán. Ý tưởng chung là xây dựng một nghiệm từng bước một và khi một nhánh nghiệm đã được thử hết thì quay lại từng bước để xây dựng các nghiệm khác.

Cách tiếp cận này không phải lúc nào cũng áp dụng được, có những bài toán mà ta không thể sinh ra tất cả các nghiệm theo cách từng nghiệm một như vậy. Tuy nhiên, trường hợp thường xảy ra là tập nghiệm của một bài toán trùng với một loại cấu hình tổ hợp nào đó. Thông thường đó là tập các hoán vị (với số phần tử cho trước), nhưng đôi lúc cũng có thể là các cấu hình khác (tổ hợp, số cách phân chia một tập hợp, ...)

Lưu ý là ta luôn luôn có thể sinh ra tất cả các chuỗi của 0 và 1, kiểm tra từng chuỗi một (kiểm tra xem chuỗi đó có tương ứng với một nghiệm hợp lệ hay không) và lưu lại nghiệm tốt nhất. Nếu ta có thể tìm một cận trên của kích cỡ nghiệm tốt nhất, số nghiệm phải kiểm tra là hữu hạn. Tuy nhiên cách làm này không đủ nhanh và không nên dùng nó nếu có cách làm khác.

## Ví dụ 2
Một thuật toán quay lui đơn giản để sinh ra tất cả các hoán vị của các số tự nhiên từ 0 tới $N-1$

~~~cpp
vector<int> permutation(N);
vector<int> used(N,0);

void try(int which, int what) {
  // try taking the number "what" as the "which"-th element
  permutation[which] = what;
  used[what] = 1;

  if (which == N-1)
    outputPermutation();
  else
    // try all possibilities for the next element
    for (int next=0; next<N; next++)
      if (!used[next])
        try(which+1, next);

  used[what] = 0;
}

int main() {
  // try all possibilities for the first element
  for (int first=0; first<N; first++)
    try(0,first);
}
~~~

Trong trường hợp này, dễ thấy cận dưới chính là số lượng nghiệm khả dĩ của bài toán. Thuật toán quay lui thường được sử dụng để giải các bài toán khó - khi ta không tìm được thuật toán nào tối ưu hơn. Thường thì không gian nghiệm khá lớn và phân bố đồng đều, thuật toán có thể được cài đặt sao cho độ phức tạp gần với đánh giá cận dưới. Để tìm cận trên ta chỉ việc cộng thêm số lượng phép tính cần thiết trong thực tế.

Tuy vậy cách làm này thường là không khả thi do nó phải khảo sát một số lượng lớn các nghiệm - thường là hàm mũ hoặc lớn hơn thế.

# Chia để trị sử dụng đệ quy

Từ ví dụ 2 chúng ta có thể nhầm tưởng rằng đệ quy chạy không hiệu quả và làm cho tốc độ thực thi rất chậm. Không phải lúc nào điều này cũng đúng. Ngược lại, đệ quy có thể là một công cụ rất mạnh để thiết kế những thuật toán hiệu quả. Cách thông thường để thiết kệ một giải thuật đệ quy hiệu quả là áp dụng tư tưởng **Chia để Trị** - chia bài toán thành nhiều phần, xử lý các phần nhỏ tách biệt nhau và cuối cùng ghép các kết quả con lại để được kết quả cho bài toán lớn. Dễ thấy rằng, phần "xử lý các phần nhỏ tách biệt nhau" thường được cài đặt bằng đệ quy - tiếp tục chia phần nhỏ thành phần nhỏ hơn cho tới khi đủ nhỏ để giải trực tiếp bằng các thuật toán đơn giản.

## Ví dụ 3
Mã giả mô tả thuật toán sắp xếp trộn *MergeSort*
~~~cpp
MergeSort(mảng S) {
  if (số phần tử của S nhỏ hơn hoặc bằng 1) return S;
  chia đôi S thành hai mảng con S1 và S2 với số phần tử gần bằng nhau;
  MergeSort(S1);
  MergeSort(S2);
  ghép S1 và S2 đã sắp xếp để thu được S mới đã sắp xếp;
  return S mới;
}
~~~

Ta thấy là chỉ cần $O(N)$ (hoặc $O(1)$, tùy vào cách cài đặt) để chia một mảng $N$ phần tử thành hai mảng con. Ghép hai mảng con ngắn hơn đã sắp xếp này có thể làm trong $ \Theta(N)$: khởi tạo mảng $S$ rỗng. Tại mỗi bước phần tử nhỏ nhất mà chưa có trong $S$ là phần tử đầu của $S1$ hoặc $S2$. Lấy phần tử này cho vào cuối của $S$ và cứ thế tiếp tục.

Như vậy tổng độ phức tạp cần để $MergeSort$ một mảng với $N$ phần tử là $\Theta(N)$ cộng với thời gian thực hiện hai lệnh gọi đệ quy.

Gọi $f(N)$ là độ phức tạp của thuật toán *MergeSort* ở trên. Theo suy luận ở trên ta có:
$$
f(N) = f(\lfloor N/2 \rfloor) + f(\lceil N/2 \rceil) + p(N)
$$

Với $p$ là hàm tuyến tính biểu thị tổng chi phí tính toán dành cho việc chia đôi mảng ban đầu và ghép hai mảng con vào kết quả cuối.

Công thức trên được gọi là công thức truy hồi. Nếu bạn không biết thuật ngữ này thì cũng không cần lo lắng. Từ "truy hồi" (recurrence) trong tiếng Latin có nghĩa là "chạy về phía sau". Vì vậy "công thức truy hồi" có nghĩa là giá trị của hàm $f$ được tính theo giá trị trước đó (đầu vào nhỏ hơn) của $f$.

Để định nghĩa hoàn chỉnh một công thức truy hồi, ta cần chỉ ra giá trị của một vài trường hợp khởi tạo cơ bản - trong trường hợp này là $f(1)$. Các giá tị này (và hàm $p$) sẽ cho phép ta tính toán chính xác giá trị của hàm $f$.

Tuy nhiên, như ta đã thấy ở phần 1, giá trị chính xác của hàm $f$ không phải là mục tiêu cần tính. Mặc dù về mặt lý thuyết ta có thể tính cụ thể biểu thức của hàm $f(N)$ theo dạng đóng, biểu thức đó có thể rất phức tạp và không thật sự cần thiết. Trong thực tế, ta chỉ quan tâm tới đánh giá $\Theta$ (hoặc cận trên $O-lớn$) của độ tăng của hàm $f$. Thông thường các đánh giá này có thể tính được một cách khá thuận lợi nếu ta nắm được các phương pháp tính thông dụng.

Vì lý do trên, ta sẽ không cần tới dạng chính xác của hàm $p$ mà chỉ cần biết rằng $p(N) =  \Theta(N)$. Thêm vào đó, ta không cần giá trị khởi tạo của $p$. Ta chỉ cần biết rằng với $N$ nhỏ thì giá trị của $p$ sẽ dễ dàng tính được với độ phức tạp là hằng số.

Lý do đằng sau việc đơn giản hóa $p$ như trên là do một nhận xét: việc thay đổi các giá trị khỏi tạo chỉ thay đổi nghiệm của công thức truy hồi chứ không thay đổi cận trên tiệm cận của hàm số. (Bạn có thể thử bằng cách tìm một hàm $p$ bất kỳ và tính $f(8), f(16)$ và $f(32)$ với các giá trị $f(1)$ khác nhau).

Bên cạnh đó, vì đây chỉ là bài viết mang tính giới thiệu nên chúng ta sẽ không bàn đến các lý thuyết để xử lý các phép lấy phần nguyên, làm tròn lên và làm tròn xuống. Ta sẽ đơn giản bỏ qua các phép toán đó (ví dụ ta sẽ coi các phép chia luôn là chia lấy nguyên và làm tròn xuống).

Các bạn có kỹ năng toán tốt nên thử tự chứng minh mệnh đề sau đây: nếu $p$ là hàm đa thức (với $N$ không âm) và $q(n) = p(n+1)$ thì $q(n) = \Theta(p(n))$. Mệnh đề trên cho phép ta chứng minh (với $f$ bị chặn trên bởi một hàm đa thức) rằng vế phải của công thức truy hồi có độ tăng tiệm cận không thay đổi khi ta thay phép làm tròn xuống bởi phép làm tròn lên.

Nhận định trên cho phép ta viết lại công thức truy hồi ở trên theo cách đơn giản hơn:
$$
f(N) = 2f(N/2) + \Theta(N) \space\space\space(1)
$$

Lưu ý rằng đây không phải là một "phương trình" theo nghĩa truyền thống. Ở phần 1 ta đã thấy rằng dấu bằng ở đây có nghĩa là **"tiệm cận bằng"**. Thông thường có rất nhiều hàm số khác nhau thỏa mãn phương trình trên. Tuy nhiên tất cả các hàm số đó sẽ có cùng độ tăng - và đây chính là điều mà ta hướng tới. Tổng quát hơn, ta muốn tìm cận trên nhỏ nhất của độ tăng của tất cả các hàm số thỏa mãn phương trình trên.

Trong các phần cuối cùng của bài viết này, ta sẽ bàn luận một vài phương pháp giải các "phương trình" trên. Tuy nhiên trước đó ta sẽ tìm hiểu thêm một chút về các hàm logarit.

# Lưu ý về hàm logarit
Tới đây bạn có thể đặt câu hỏi: tác giả viết một vài thuật toán có độ phức tạp là hàm logarit ví dụ $O(NlogN)$, vậy cơ số của hàm logarit này là bao nhiêu? Tại sao ta không sử dụng cơ số 2 để có $O(Nlog_2N)$?

Câu trả lời: cơ số của hàm logarit không quan trọng, tất cả cac hàm logarit (với cơ số lớn hơn 1) đều tiệm cận bằng nhau. Lý do là hai hàm logarit khác nhau tỷ lệ với nhau:

$$
	log_aN = \frac{log_bN}{log_ba}  		\space\space\space(2)
$$

Lưu ý là với hai cơ số $a, b > 1$ thì tỷ lệ này là hằng số $log_ba$. 

Nhằm mục đích viết rõ ràng và dễ đọc, ta luôn sử dụng ký hiệu chung $logN$ bên trong hàm $O-lớn$, kể cả khi các hàm logarit khác nhau được sử dụng khi tính cận của độ phức tạp. 

Bên cạnh đó, ý nghĩa của cách viết $logN$ khác nhau giữa các quốc gia khác nhau. Để tránh nhầm lẫn ta quy ước như sau: $logN$ để chỉ cơ số $10$, $lnN$ để chỉ cơ số tự nhiên, $lgN$ cho cơ số $2$ và $log_bN$ cho các trường hợp chung khác. 

Tiếp theo đây ta sẽ xem xét một phài mẹo biến đổi hữu ích được dùng trong các phần sau. Gọi $a, b$ là các hằng số cho trước với $a, b > 1$. 
Từ (2) ta có:

$$
log_ab = \frac{log_bb}{log_ba} = \frac{1}{log_ba}
$$

Sử dụng tính chất trên để biến đổi $a^{log_bN}$ ta được:
$$
a^{log_bN} = a^{log_aN/log_ab} = (a^{log_aN})^{1/log_ab} = N^{log_ba} \space\space\space(3)
$$

# Phương pháp Thay Thế

Phương pháp này có thể được tổng kết trong một câu: dự đoán cận trên (tiệm cận) của $f$ và (cố gắng) chứng minh bằng quy nạp.

Để minh họa, ta sẽ chứng minh rằng hàm $f$ thỏa mãn phương trình (1) là $O(NlogN)$
Từ (1) ta có:

$$
\forall N; f(N) \leq 2f(N/2) + cN
$$

với một hằng số $c$ nào đó. Ta sẽ chứng minh rằng tồn tại một hằng số $d$ đủ lớn nào đó mà với mọi $N$ lớn ta có $f (N) \leq dN lg N$. Ta sẽ chứng minh bằng quy nạp.

Giả sử $f (N/2) \leq d (N/2)lg(N/2)$. Ta có:

![](new57.png)

Nói cách khác, phép quy nạp sẽ đúng nếu $d>c$. Ta luôn luôn có thể chọn $d$ lớn thỏa mãn điều kiện này.

Để hoàn thiện ta cần chứng minh rằng bất đẳng thức trên đúng với một vài giá trị đầu tiên của $N$. Phép chứng minh khá phức tạp. Ý tưởng chính là nếu giá trị $d$ ta tìm được chưa đủ lớn, ta luôn có thể tăng $d$ sao cho các trường hợp đầu tiên của $N$ thỏa mãn bất đẳng thức.

Lưu ý rằng trong ví dụ trên ta không thể chứng minh khi $N = 1$ với vì $lg1 = 0$. Tuy nhiên, điều này không ảnh hưởng tới tính đúng đắn của phép chứng minh trên. Kết luận: từ (1) ta có  $f (N) = O(N lg N)$. 

# Phương pháp Cây Đệ Quy
Với một người mới bắt đầu thì phương pháp trên không hữu dụng lắm. Để sử dụng phương pháp Thay Thế ta cần phải có một dự đoán tốt về cận trên của độ phức tạp, và để có dự đoán tốt đó ta cần có một vài thông tin, hiểu biết về hàm độ phức tạp trước. Câu hỏi là, làm thế nào để thu thập các hiểu biết này? Trước tiên ta sẽ xem xét kỹ hơn về cơ chế chạy đệ quy của nó của hàm số trên (bằng việc chạy thử từng bước đệ quy của nó).

Ta có thể biểu diễn các bước thực thi của một chương trình đệ quy trên một bộ đầu vào cho trước bằng một cây có gốc xác định. Mỗi đỉnh trên cây sẽ tương ứng với một bài toán con mà chương trình đang giải. Xét một đỉnh bất kỳ trên cây. Nếu giải bài toán thuộc đỉnh đó cần phải gọi đệ quy, đỉnh đó sẽ có các đỉnh con tương ứng với các bài toán nhỏ hơn nữa. Gốc của cây là bộ đầu vào, các lá tương ứng với các bài toán cơ bản có thể giải trực tiếp bằng các thuật toán thông thường (không đệ quy).

Giả sử rằng ta đánh dấu mỗi đỉnh bằng một nhãn biể thị độ phức tạp nội tại cần có trên đỉnh đó (không tính tới độ phức tạp của lệnh gọi đệ quy). Rõ ràng là độ phức tạp của bài toán gốc bằng tổng tất cả các nhãn của các đỉnh.

Tương tự như các phần trên, ta chỉ quan tâm tới cận trên tiệm cận. Để tìm giá trị này ta có thể "làm tròn" mỗi nhãn để việc tính tổng dễ dàng hơn. Ta minh họa cách làm trên bằng một vài ví dụ sau:

## Ví dụ 4
Cây đệ quy cho thuật toán *MergeSort* ở Ví dụ 3 với 5 phần tử.
![](tree1.png)

Cây đệ quy cho công thức truy hồi tương ứng của *MergeSort*. Số trong mỗi đỉnh biểu thị số bước mà thuật toán thực thi tại đỉnh đó.

![](tree2.png)

## Ví dụ 5
Cây đệ quy trong trường hợp xấu nhất của phương trình (1):

![](tree3.png)

Một cách xử lý phổ biến trong toán tổ hợp là tính tổng các cấu hình theo thứ tự mới khác với thứ tự mà các tổ hợp được tạo ra. Trong trường hợp này ta tính tổng theo từng mức trên cây (các đỉnh có cùng độ sâu). Không khó để nhận ra rằng tổng độ phức tạp ở mỗi mức là $cN$.

Câu hỏi thứ hai là: cây trên có bao nhiêu mức? Rõ ràng là lớp lá tương ứng với trường hợp cơ bản của thuật toán. Chú ý là kích cỡ mảng cần xử lý giảm một nửa khi đi từ mức trên xuống mức dưới. Vì sau $lgN$ bước ta có bài toán cơ bản với mảng có $1$ phần tử, chiều cao của cây (tổng số mức) sẽ là $\Theta(logN)$.

Từ hai nhận xét trên ta thu được kết quả cuối cùng: tổng độ phức tạp cần thực hiện là 
$ \Theta(cN log N) = \Theta(N log N)$.

Nếu bạn chưa hoàn toàn tin tưởng vào kết quả vừa thu được thì có thể áp dụng phương pháp Thay Thế ở trên để kiểm tra lại. Trong phần sau ta sẽ thấy là tồn tại những định lý cụ thể để có thể chứng minh chặt chẽ kết quả thu được ở trên.


# Cây Đệ Quy mở rộng

Ví dụ 5 ở trên cho ta một câu hỏi: việc tổng độ phức tạp ở mỗi mức của cây bằng nhau có phải là trùng hợp hay không?

Trả lời: Không và Có. Không, vì một lý do đơn giản mà ta sẽ xem ở phần sau. Có, vì không phải lúc nào tổng các mức cũng bằng nhau như vậy - hai ví dụ sau đây sẽ minh họa cho điều đó.

## Ví dụ 6

Ta thử áp dụng phương pháp Cây Đệ Quy để giải cho phương trình sau:
$$
f(N) = 3f(N/2) + \Theta(N^3)
$$

Cây đệ quy sẽ có dạng sau:

![](tree5.png)

Thử tính toán độ phức tạp tại vài mức đầu tiên, ta có:

<table>
<tbody>
<tr>
<td>level</td>
<td>1</td>
<td>2</td>
<td>3</td>
<td>…</td>
</tr>
<tr>
<td>work</td>
<td>$cN$</td>
<td>$ {3\over 8}cN^3 $</td>
<td>$ {3^2 \over 8^2}cN^3 $</td>
<td>...</td>
</tr>
</tbody>
</table>


Rõ ràng là ta càng đi sâu xuống cây thì tổng độ phức tạp càng giảm. Vậy tốc độ giảm là bao nhiêu? Khi ta đi xuống một mức thì sẽ phải giải số bài toán con gấp ba lần số bài toán ở mức hiện tại. Tuy nhiên, vì mỗi bài toán con chỉ phải giải có kích cỡ giảm một nửa, nên thời gian cần để giải bài toán con giảm còn bằng $1 \over 8$ bài toán cha. Như vậy tổng độ phức tạp giảm theo hệ số $3 \over 8$.

Điều này có nghĩa là toàn bộ bảng số ở trên sẽ hình thành một dãy cấp số nhân. Giả sử rằng dãy cấp số nhân đó tăng tới vô cùng. Tổng của dãy sẽ là:

$$
S = \frac{cN^3}{1 - \frac{3}{8}} = \frac{8}{5}cN^3 = \Theta(N^3)
$$

Như vậy tổng độ phức tạp trên cây đệ quy là $O(N^3)$ (tổng tới vô cùng cho ta cận trên). Ta cũng thấy là ngay phần từ đầu tiên của dãy cấp số nhân đã là $ \Theta(N^3)$. Vậy ta kết luận tổng độ phức tạp của cây đệ quy trên là $ \Theta(N^3)$.

Một nguyên lý tổng quát quan trọng ta có thể rút ra từ ví dụ này là: nếu tổng độ phức tạp của các mức của cây tạo nên một dãy cấp số nhân giảm, thì tổng độ phức tạp trên cả cây sẽ tiệm cận bằng với độ phức tạp ở gốc của cây.

Từ kết quả trên ta có một nhận xét quan trọng về thuật toán đệ quy biểu diễn bằng công thức truy hồi có tính chất trên: lệnh gọi đệ quy giải bài toán con không tốn thời gian thực thi bằng việc chuẩn bị lời gọi và xử lý sau lời gọi đệ quy. (Nói cách khác, nếu ta cần cải tiến thuật toán thì phải tập trung tối hưu hóa hai việc đó).

## Ví dụ 7
Giờ chúng ta cùng thử áp dụng phương pháp Cây Đệ Quy để giải phương trình sau:
$$
f(N) = 5f(N/3) + \Theta(N)
$$
Cây đệ quy sẽ có dạng sau
![](tree4.png)

Như trên, thử tính số lệnh cần thực thi ở vài mức đầu tiên. Ta có:

<table>
<tbody>
<tr>
<td>level</td>
<td>1</td>
<td>2</td>
<td>3</td>
<td>…</td>
</tr>
<tr>
<td>work</td>
<td>$cN$</td>
<td>${5\over 3}cN$</td>
<td>${5^2 \over 3^2}cN$</td>
<td>...</td>
</tr>
</tbody>
</table>

Ta có kết quả ngược với ví dụ 6: khi ta càng đi sâu xuống dưới thì tổng độ phức tạp lại càng tăng lên. Khi ta đi xuống một  mức, sẽ có gấp $5$ lần số bài toán con, mỗi bài toán con sẽ có kích cỡ bằng $1 \over 3$ bài toán cha. Vì thời gian xử lý là tuyến tính với kích cỡ bài toán nên ta có tổng độ phức tạp ở mức sau tăng gấp $5 \over 3 $ mức trước.

Vẫn như trên ta hướng tới việc tính tổng độ phức tạp trên cả cây. Lần này việc tính toán sẽ khó hơn vì lượng công việc phải tính nằm ở mức sâu nhất. Ta cần biết độ sâu của cây.

Mức thấp nhất có bài toán với kích cỡ bằng $1$. Tổng quát, kích cỡ bài toán con ở mức $k$ là $N \over 3^k$. Giải phương trình $1 = N \over 3^k$ ta được $k = log_3N$. Lưu ý là ở đây ta viết rõ chỉ cơ số của hàm logarit vì cơ số này quan trọng trong việc phản ánh cấu trúc cây.

Như vậy cây đệ quy có $log_3N$ mức. Mỗi mức có $5$ lần số đỉnh so với mức trên nó, nên mức cuối cùng có $5^{log_3N}$ đỉnh. Tổng độ phức tạp ở mức cuối tương ứng là $c5^{log_3N}$.

Sử dụng phương trình (3) ta viết lại giá trị này là $cN^{log_35}$.

Để tính tổng độ phức tạp trên toàn cây ta **đảo ngược** cây, tạo thành một dãy cấp số nhân **giảm** và như vậy ta có thể áp dụng cách tính ở trên. Xử lý tương tự ví dụ trước đó ta thu được tổng độ phức tạp là một giá trị tiệm cận bằng với phần tử lớn nhất trong dãy cấp số nhân.

Ta kết luận rằng tổng độ phức tạp của thuật toán biểu diễn bởi phương trình trên là xấp xỉ $\Theta(N^{log_35}) \approx \Theta(N^{1.465}) $.

Lưu ý là cơ số 3 trong hàm logarit cho ta kết quả mũ chính xác, vì vậy cơ số này rất quan trọng. Nếu là cơ số khác thì giá trị tiệm cận cũng sẽ thay đổi.

# Định lý Tổng Quát

Từ các ví dụ trên chúng ta đã thấy một quy luật giải các công thức truy hồi. Cho một công thức truy hồi, lập cây đệ quy tương ứng và tính tổng độ phức tạp trên mỗi mức. Kết quả thu được sẽ là một dãy cấp số nhân. Nếu đó là dãy giảm, tổng độ phức tạp trên toàn cây sẽ tỷ lệ với độ phức tạp của đỉnh gốc. Nếu là dãy tăng, tổng độ phức tạp sẽ tỷ lệ với  tổng độ phức tạp ở các lá. Nếu là dãy không đổi thì tổng độ phức tạp sẽ là (độ phức tạp trên một mức) nhân với (chiều cao cây).

Trong thực tế sẽ có một vài trường hợp mà quy luật trên gặp khó khăn, tuy nhiên hầu hết sẽ chỉ có một trong ba trường hợp trên xảy ra. Thêm vào đó, ta có cơ sở để chứng minh quy luật trên một cách chặt chẽ. Cơ sở chính thống của quy luật trên được biết đến với cái tên Định lý Tổng Quát.

Để thuận tiện bài viết này sẽ trình bày đầy đủ về định lý này. (Lưu ý là ta không cần biết chứng minh của nó để có thể áp dụng vào giải công thức truy hồi).

Cho $a \geq 1$ và $b > 1$ là hai hằng số nguyên dương. Gọi $p$ là một hàm số nguyên **không giảm**. Gọi $f$ là một hàm số bất kỳ thỏa mãn

$$
f(N) = af(N/b) + p(N)
$$
Ta có kết quả sau: 

1. Nếu $p(N) = O(N^{(log_ba) - \varepsilon})$ với một số $ \varepsilon$ > 0 nào đó thì $f(N) = \Theta(N^{log_ba})$
2. Nếu $p(N) = O(N^{(log_ba) - \varepsilon})$  thì $f (N) = \Theta(p(N)log N)$.
3. Nếu $p(N) = \Omega(N^{(log_ba) - \varepsilon})$ với một số $ \varepsilon$ > 0 nào đó, và nếu $ap(N/b) \leq cp(N)$ với $c < 1$ khi $N$ đủ lớn thì $ f (N) = \Theta(p(N))$.
 

Trường hợp $1$ tương với **Ví dụ 7**. Hầu hết thời gian thực thi được dành cho việc gọi lệnh đệ quy và số lần gọi đệ quy là đáng kể.

Trường hợp $2$ tương ứng với **Ví dụ 5**. Thời gian dành cho việc gọi đệ quy xấp xỉ bằng thời gian để chuẩn bị cho lệnh gọi đệ quy và xử lý sau đó. Trên tất cả các mức của cây ta có độ phức tạp xấp xỉ bằng nhau, chiều cao cây luôn là một hàm logarit của kích cỡ tập đầu vào.

Trường hợp $3$ tương ứng với **Ví dụ 6**. Hầu hết thời gian thực thi được dành cho việc chuẩn bị để gọi lệnh đệ quy và xử lý kết quả sau đó. Thông thường thì tổng độ phức tạp sẽ tiệm cận bằng với thời gian thực thi ở đỉnh gốc của cây.

Lưu ý điều kiện thêm vào ở trường hợp $3$. Để trường hợp $3$ đúng ta cần có điều kiện của hàm $p$ phải thỏa mãn thời gian thực thi hàm $p$ lớn hơn tổng thời gian thực thi ở các đỉnh con cháu. Thật ra đây không phải là một vấn đề cần phải chú tâm quá nhiều bởi trong các kỳ thi các hàm $p$ mà bạn có thể gặp hầu như sẽ thỏa mãn điều kiện trên (nếu rơi vào trườn hợp $3$).


## Ví dụ 8

Gọi $f(N)$ là thời gian mà thuật toán ** Nhân ma trận Strassen** cần để nhân hai ma trận vuông kích cỡ $N$ x $N$. Đây là một thuật toán đệ quy, thực hiện $7$ lời gọi hàm đệ quy, mỗi hàm nhân hai ma trận có kích cỡ $N/2$ x $N/2$ và sau đó tổng hợp kết quả trong $\Theta(N^2)$.

Ta có công thức truy hồi sau:

$$
f(N) = 7f(N/2) + \Theta(N^2)
$$


Sử dụng định lý Tổng Quát, ta thấy Trường hợp $1$ có thể áp dụng được. Vì vậy độ phức tạp của thuật toán Strassen là $\Theta(N^{log_27}) \approx \Theta({N^{2.807}})$. Lưu ý là thuật toán cổ điển nhân ma trận theo định nghĩa có độ phức tạp $ \Theta(N^3)$. 

## Ví dụ 9
Thỉnh thoảng ta có thể gặp trường hợp mà kích cỡ các bài toán con không bằng nhau. Một ví dụ là thuật toán **Trung vị của 5** để tìm phần tử lớn thứ *k* của một mảng số. Thuật toán trên được chứng minh là có độ phức tạp thỏa mãn công thức

$$
f(N) = f(N/5) + f(7N/10 + 6) + \Theta(N)
$$

Công thức trên giải như thế nào? Phương pháp cây Đệ Quy có thể được áp dụng trong trường hợp bất đối xứng như vậy không? Có một phiên bản tổng quát hơn của Định lý Tổng Quát áp dụng cho trường hợp như vậy hay không? Và trong các trường hợp mà định lý Tổng Quát không áp dụng được, điển hình là với công thức $f (N) = 4f (N/4) + \Theta(N log N)$, ta cần xử lý thế nào?

Chúng ta sẽ không trả lời các câu hỏi trên tại đây, và tài liệu này cũng không phải là tài liệu duy nhất về chủ đề độ phức tạp thuật toán. Nếu bạn đang thắc mắc về các câu hỏi trên thì bạn đã nắm được cơ bản đủ để sử dụng trong các kỳ thi thuật toán. Nếu bạn muốn trả lời các câu hỏi trên thì có thể tìm đọc trong các sách chính thống.

Cảm ơn vì đã theo dõi bài viết tới cuối. Nếu có câu hỏi, góp ý hoặc báo lỗi, bạn có thể sử dụng forum của TopCoder.

# Lời người dịch
Trong bài viết 2 phần này tác giả **misof** đã giới thiệu khá đầy đủ về độ phức tạp tính toán để có thể sử dụng trong các kỳ thi lập trình. Tác giả đã bỏ qua một vài điểm như xử lý phần nguyên, chứng minh độ phức tạp bằng phép tính lấy giới hạn, lời giải cho phần 1 của Ví dụ 9 (xem lời giải tại [đây](http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-design-and-analysis-of-algorithms-spring-2012/lecture-notes/MIT6_046JS12_lec01.pdf)), định lý Tổng Quát mở rộng (dùng để giải phần 2 của ví dụ 9) và một vài chi tiết khác. Bạn đọc quan tâm tới các phần bị bỏ qua có thể tìm đọc cuốn **Introduction to Algorithm, 3rd edition** [link](http://bayanbox.ir/view/4177858657730907268/introduction-to-algorithms-3rd-edition.pdf) thường được biết đến với tên gọi **CLRS** (4 chữ cái đầu tên của 4 tác giả), hình như đã có bản dịch tiếng Việt. Các bạn yêu thích học trực tuyến có thể tìm khóa **Analysis and Design of Algorithms** trên trang web *mentorsnet.org* (bằng tiếng Anh), đây là khóa học của giảng viên Ấn Độ và họ có slides bài giảng rất chi tiết gồm cả toàn bộ chứng minh của định lý Tổng Quát cơ bản và mở rộng. Ngoài ra, sau khi đã thuần thục về độ phức tạp tính toán các bạn có thể tìm hiểu thêm về các khái niệm lớp $P$ và $NP, NP-Hard, NP-Complete$. Hiểu biết về $P$ và $NP$ sẽ giúp các bạn tiếp cận với một dạng bài đang trở nên phổ biến gần đây là **tham số cố định khả tính** (*fixed-parameter-tractability* hay *FPT*). Bạn có thể tìm hiểu về *FPT* qua bài viết trên blog của **Petr** tại http://petr-mitrichev.blogspot.com/2016/07/a-fixed-parameter-tractable-week.html. Tiềm năng của *FPT* theo mình nghĩ là rất lớn với ứng dụng không chỉ trong việc thi các kỳ thi thuật toán mà còn trong giải các bài toán thực tế.