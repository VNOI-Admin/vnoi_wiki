[[_TOC_]]

# FFT

Tác giả: ngmq

Trong bài này chúng ta sẽ tìm hiểu về thuật toán nhân nhanh hai đa thức sử dụng phép biến đổi Fourier nhanh (*Fast Fourier Transform - FFT*) và cách cài đặt của nó. Bài viết này sẽ chỉ nêu chứng minh sơ lược của một vài tính chất được sử dụng. Các chứng minh chi tiết có thể tìm thấy ở mục tài liệu tham khảo phía cuối của bài viết.

# Vài nét lịch sử

Phép biến đổi Fourier (*Fourier Transform*) là một trong số những phát kiến toán học đặc sắc có lịch sử hào hùng, gắn liền với những phát kiến khoa học và chiến tranh quân sự ở thế kỷ 19 và 20. **Joseph Fourier** (1768-1830) là một nhà khoa học làm việc trong đội quân thám hiểm Ai Cập của Napoleon từ năm 1798. Sau khi cách mạng Pháp kết thúc năm 1799, Fourier trở về Pháp và tham gia xây dựng lại đất nước trong vai trò một giáo sư của đại học École Polytechnique. Trong quá trình làm việc với các công trình xây dựng cầu đường và đóng tàu, ông đặc biệt quan tâm tới bài toán mô tả quá trình truyền dẫn nhiệt trong kim loại, điều dẫn tới sự ra đời của phép biến đổi Fourier liên tục vào năm 1807 trong một báo cáo của ông tại viện hoàng gia Paris. Trong đó, ông mô tả mọi hàm số, kể cả các hàm số không liên tục đều có thể được biểu diễn dưới dạng tổng của một số vô hạn các hàm số lượng giác. Phát biểu này của Fourier gây chấn động và ấn tượng tới mức nhà toán học Pháp cùng thời là **Lagrange** cho rằng việc nghĩ ra phát kiến này là *gần như không thể* ("nothing short of impossible") [1]. Trong hơn một trăm năm sau đó phép biến đổi Fourier trở thành một đối tượng nghiên cứu phổ và liện tục được phát triển, hoàn thiện bởi vô số các tên tuổi lớn của toán lý thuyết [2].

Trong khi phiên bản nguyên thủy có lịch sử hoành tráng như vậy, phép biến đổi Fourier nhanh, dù được cho là ra đời trước, lại được quan tâm chậm hơn nhiều. Người ta cho rằng những ý tưởng đầu tiên về biến đổi Fourier nhanh được phát triển bởi nhà toán học Đức **Carl Friedrich Gauss** (1777 - 1855) vào năm 1805 khi ông cố gắng xác định quỹ đạo của các thiên thạch [3], nhưng ông không công bố kết quả của mình. Mối liên hệ giữa Gauss và phép biến đổi Fourier nhanh chỉ được phát hiện khi các công trình của ông được tập hợp và công bố vào năm 1866. Mặc dù vậy, vào thời đó không có ai quan tâm tới công trình này vì lý thuyết độ phức tạp tính toán chưa phát triển (mãi tới năm 1936 **Alan Turing** mới phát triển mô hình tính toán đầu tiên, và phải tới năm 1965 thì lịch sử ngành nghiên cứu về độ phức tạp tính toán mới bắt đầu với công trình của **Hartmanis** và **Stearns** [4]). Cũng trong năm 1965 hai nhà toán học trong ban cố vấn khoa học của tổng thống Mỹ Kennedy là **James Cooley** và **John Tukey** đã tự tìm ra phép biến đổi nhanh Fourier trong khi thiết kế hệ thống phát hiện các vụ thử hạt nhân của chính quyền Xô Viết [3]. Kể từ thời điểm đó phép biến đổi nhanh Fourier mới chính thức được quan tâm và nghiên cứu ứng dụng trong rất nhiều các lĩnh vực nghiên cứu khác nhau của vật lý, sinh học, điện tử, y tế, điều khiển học...

# Phép nhân hai đa thức

Cho hai đa thức $p(x), q(x)$ có bậc $d, e$ như sau:

$$
p(x) = a_0 + a_1 x + a_2 x^2 + ... + a_d x^d
$$
$$
q(x) = b_0 + b_1 x + b_2 x^2 + ... + b_e x^e
$$

Ta cần tìm tích $c(x)$ của hai đa thức trên, có dạng:
$$
c(x) = p(x)q(x) = c_0 + c_1 x + c_x x^2 + ... + c_{d+e} x^{d+e}
$$

trong đó

$$
c_{j} = \sum_{i=0}^j a_ib_{j-i} \qquad j = 0, 1, ..., d+e
$$

Cách làm theo định nghĩa là ta nhân mỗi hệ số của $p(x)$ với tất cả các hệ số của $q(x)$ rồi cộng các hệ số của cùng tổng số mũ. Vì hai đa thức có $d+1$ và $e+1$ hệ số nên cách làm này có độ phức tạp là $O((d+1)(e+1)) = O(de)$. Khi $d$ và $e$ tương đối lớn cỡ $10^3$ hoặc $10^4$ trở lên thì độ phức tạp này là quá lớn để chạy trên máy tính, đặc biệt là các máy tính nhúng đòi hỏi tốc độ tính toán nhanh. Phép biến đổi FFT giúp thực hiện phép nhân nói trên trong độ phức tạp $O(N*logN)$ trong đó $N$ là lũy thừa của $2$ nhỏ nhất lớn hơn $d$ và $e$.
 
# Biểu diễn đa thức qua ma trận Vandermonde


*Kể từ phần này trở về sau, ta quy ước $n$ là số hệ số của đa thức (bậc $n-1$) và $n$ là một lũy thừa của 2 ($n = 2, 4, 8, 16, 32, 64...$).*

Xét đa thức $p(x) = a_0 + a_1 x + a_2 x^2 + ... + a_{n-1} x^{n-1}$ với bậc $n-1$ và các hệ số phức $a_i \in \mathbb{C}$. Biểu thức tính $n$ giá trị của $p(x)$ tại $n$ điểm $z_0, z_1, ... z_{n-1}$ có thể biểu diễn qua phép nhân ma trận như sau: 

$$
\begin{bmatrix}
    1       & z_0^1 & z_0^2 & \dots & z_0^{n-1} \newline
       1      & z_1 & z_1^2 & \dots & z_1^{n-1} \newline
    \ldots & \ldots & \ldots & \ldots & \ldots\newline
       1       & z_n^1 & z_n^2 & \dots & z_{n-1}^{n-1}
\end{bmatrix}
\begin{bmatrix}
    a_0 \newline a_1 \newline \vdots  \newline a_{n-1}
\end{bmatrix}
=
\begin{bmatrix}
    p(z_0) \newline p(z_1) \newline \vdots  \newline p(z_{n-1})
\end{bmatrix} \space (1)
$$

Ma trận vuông $V$ kích cỡ $n*n$ của $z_{0:{n-1}}$ ở trên được gọi là ma trận Vandermonde. 
Ta có các định lý sau:

**Định lý 1:** Định thức của ma trận Vandermonde là 
$$det(V) = \prod_{0 \leq i < j \leq n-1}(z_j - z_i)$$

**Chứng minh (sơ lược):** 
Với mỗi hàng $i = 0, 1, ...n-2$ ta liên tục thay hàng $j = i+1, i+2, ...n-1$ bằng hiệu của các hệ số của hàng $j$ trừ đi hàng $i$. Đây là phép biến đổi cơ bản nên giá trị định thức cần tính không đổi. Lấy nhân tử chung $z_j - z_i$ ở tất cả các hàng ra ngoài và xét tiếp hàng $i+1$. Sau khi xét xong $i = n-2$ ta được một ma trận chéo có đường chéo chỉ gồm $z_{ii} = 1$, định thức của ma trận này hiển nhiên bằng 1. Vì vậy định thức cần tính là tích của tất cả các nhân tử chung bỏ ra ngoài ở các bước trước đó.

Phép chứng minh bằng quy nạp có thể xem thêm tại [đây](https://proofwiki.org/wiki/Vandermonde_Determinant)

**Định lý 2:** Đa thức $p(x)$ được xác định duy nhất bởi các giá trị của nó $p(z_0), p(z_1), ... p(z_{n-1})$ khi $n$ giá trị $z_0, z_1, ... z_{n-1}$ phân biệt. Ta gọi đây là *phép biến đổi ngược*.

**Chứng minh:** 

Coi phương trình $(1)$ là một hệ phương trình $n$ ẩn với bộ nghiệm $a_0, a_1, ...a_{n-1}$. Để đa thức $p(x)$ xác định và duy nhất thì định thức của ma trận $V$ ở trên phải khác $0$. Theo **Định lý 1** ta có điều phải chứng minh.

**Hệ quả:** khi $V$ khả nghịch, hệ số $a_0, a_1, ...a_{n-1}$ được xác định thông qua tích của ma trận nghịch đảo $V^{-1}$ của $V$ và $p(z_0), p(z_1), ...p(z_{n-1})$.

Từ định lý 2 ta thấy rằng thay vì lưu $n$ hệ số $a_i$, ta có thể lưu $n$ cặp giá trị $z_i, p(z_i)$. Cách biểu diễn bằng giá trị này có lợi thế là giá trị của đa thức tạo bởi tích hai đa thức được tính trong $O(1)$: $c(x) = p(x)q(x)$ trong đó $x$ là một số cho trước.

# Nghiệm nguyên thủy

Ở trên ta đã thấy là các số $z_i$ ở trên có thể chọn tùy ý miễn sao giá trị của chúng là đôi một khác nhau thì đa thức $p(x)$ là xác định và duy nhất. Ý tưởng của thuật toán FFT là chọn các giá trị $z_i$ nào đó để chuyển đổi hai đa thức cần nhân sang miền giá trị, tiến hành phép nhân trong miền giá trị này, tính ma trận nghịch đảo và chuyển đổi ngược lại từ miền giá trị sang miền hệ số. Các giá trị $z$ được chọn phải đặc biệt để hai phép tính trên (**biến đổi xuôi** và **biến đổi ngược**) có độ phức tạp nhỏ. Những giá trị đặc biệt của $z$ này được gọi là **nghiệm nguyên thủy** thỏa mãn:

$$
z^n = 1 \qquad z \in \mathbb{C} (2)
$$

với $n$ như đã quy ước và cũng là số nghiệm của phương trình $(2)$ mà ta cần. Công thức Euler xác định nghiệm thứ $k$ của phương trình $(2)$ là

$$
z_k = w_n^k = (e^{ {2\pi i}\over n})^k = e^{ {2\pi i}k\over n} = cos{{2\pi k}\over n} + isin{{2\pi k}\over n} \qquad k = 0, 1, ... n - 1
$$

trong đó $w_n$ là nghiệm mũ 1:

$$
w_n = e^{ {2\pi i}\over n} = cos{{2\pi}\over n} + isin{{2\pi}\over n}
$$

Dễ thấy là nghiệm nguyên thủy thứ $k$ có thể được tính trong $O(1)$ với $n$ đã biết.

## Một số tính chất đặc biệt của ma trận Vandermonde nghiệm nguyên thủy

**Tính chất 1:** Ma trận nghịch đảo $V^-1$ được tính bằng cách nghịch đảo lũy thừa các hạng tử trong $V$ rồi chia cho $n$. Cụ thể, hạng tử $V^{-1}[i,j] = {V[i,j]^{-1} / n}$ với $i, j = 0, 1,...n-1$ là chỉ số hàng và cột của ma trận. 

**Chứng minh (sơ lược):** gọi $B$ là ma trận kích cỡ $n * n$ tạo bởi

$$
B[i, j] = V[i,j]^{-1} \forall i, j = 0, 1,...n-1
$$

ta sẽ có $B * V = V * B = n * I$, trong đó $I$ là ma trận đơn vị.

Các bạn có thể xem chi tiết chứng minh trong slide số 17 trong tài liệu của trường DH Aalto ở phần tài liệu tham khảo.

**Hệ quả:** Độ phức tạp tính toán cho $V^{-1}$ bằng với độ phức tạp tính $V$.

**Tính chất 2:** Chia ma trận $V$ thành $4$ phần bằng nhau kích cỡ $n/2 * n/2$ theo $2$ tiêu chí: độ lớn của hàng so với $n/2$ và tính chẵn lẻ của các cột.

- Phần $I$ gồm các phần tử có chỉ số hàng   $0, 1,...n/2 - 1$ và chỉ số cột là chẵn $0, 2, 4, ...n-2$.
- Phần $II$ gồm các phần tử có chỉ số hàng  $0, 1,...n/2 - 1$ và chỉ số cột là lẻ   $1, 3, 5, ...n-1$.
- Phần $III$ gồm các phần tử có chỉ số hàng $n/2, n/2+1,...n-1$ và chỉ số cột là lẻ  $0, 2, 4, ...n-2$.
- Phần $IV$ gồm các phần tử có chỉ số hàng  $n/2, n/2+1,...n-1$ và chỉ số cột là lẻ  $1, 3, 5, ...n-1$.

[[/uploads/img4.png|alt=DivideAndConquer]]
(*Image Courtesy of Aalto University*)

Nói cách khác, ta tạo một ma trận mới $K$ bằng cách chuyển tất cả các cột có chỉ số chẵn của ma trận $V$ lên trước, các cột có chỉ số lẻ về sau, giữ nguyên thứ tự tương đối của các cột cùng chỉ số chẵn hoặc cùng chỉ số lẻ. Ở ma trận $K$ này cột $n-2$ của $V$ nằm ngay trước cột $1$ của $V$. Bốn phần $I, II, III, IV$ được tạo bởi cắt đều ma trận $V'$ thành 4 phần bằng nhau.

Ký hiệu $K_I, K_{II}, K_{III}, K_{IV}$ là bốn ma trận con của $K$. Tất cả các phần tử trong phần $II, III, IV$ đều có thể tính được từ phần $I$ theo công thức sau:

$$
K_{II}[i, j] = w_n^i K_I[i,j] \qquad \forall i, j = 0, 1, ...n/2 - 1
$$
$$
K_{III}[i,j] = K_{I}[i,j] \qquad \forall i, j = 0, 1, ...n/2 - 1
$$
$$
K_{II}[i, j] = w_n^{-i} K_I[i,j] \qquad \forall i, j = 0, 1, ...n/2 - 1
$$

**Chứng minh:** các bạn tự chứng minh hoặc xem slide số 23 trong tài liệu của trường DH Aalto ở phần tài liệu tham khảo.

# Phép biến đổi Fourier nhanh

Trong phần trên ta đã thấy vai trò của ma trận Vandermonde $V$ là biến đổi một vector cột $a_0, a_1, ...a_{n-1}$ thành một vector cột khác cùng kích cỡ $p(z_0), p(z_1), ...p(z_{n-1})$. Phép biến đổi này được gọi là "Biến đổi Fourier rời rạc" (*Discrete Fourier Transform*). Lưu ý là mặc dù hai khái niệm "Biến đổi Fourier rời rạc" (*DFT*) và "Phép biến đổi Fourier nhanh" (*FFT*) là khác nhau nhưng vì khi cài đặt DFT người ta luôn sử dụng FFT nên hai khái niệm này được coi như đồng nhất.

**Định lý 3:** Tồn tại thuật toán biến đổi Fourier rời rạc có độ phức tạp là $O(nlog_2n)$. 

**Chứng minh:** Sử dụng lại ký hiệu trong hình vẽ ở phần trên, ta gọi $X$ là vector cần biến đổi Fourier và $Y$ là vector kết quả tương ứng. Thay vì sử dụng ma trận $V$ để nhân với $X$, ta sử dụng ma trận $K$ là kết quả của phép biến đổi như trong **Định lý 2** để nhân với $X$. Lưu ý là vì $V$ đã đổi thứ tự cột nên $X$ cũng phải đổi thứ tự hàng: tất cả các hàng có chỉ số chẵn của $X$ được chuyển lên trên và các hàng chỉ số lẻ chuyển xuống dưới. Hình minh họa với $n = 4$:

[[/uploads/img5.png|alt=nis4]]
(*Image Courtesy of Aalto University*)

Tách vector kết quả $Y$ thành hai phần theo $n/2$, ta được:

[[/uploads/img6.png|alt=recursion]]

Ta quan sát là công thức tính nửa trên và nửa dưới của vector cột kết quả $Y$ sử dụng chung hai hạng tử và chỉ khác nhau về dấu của hạng tử thứ hai. Nói cách khác, chỉ cần tính được hai hạng tử tạo thành kết quả của vector kích cỡ $n/2$ là ta thu được kết quả của cả vector kích cỡ $n$ trong $O(n)$. Theo định lý tổng quát, độ phức tạp của cả quá trình là $O(nlog_2n)$

**Công thức truy hồi:**
Từ tính chất đặc biệt của ma trận $K$, ta có công thức truy hồi để biến đổi một vector cột $X$ thành vector cột $Y$ như sau:

$$
fft(x_{i=0, 1, 2,...n/2 - 1}) = fft(x_{i=0, 2, 4, ...x_{n-2}}) + w_n^i fft(x_{i=1, 3, 5...n-1})
$$

$$
fft(x_{i=n/2, n/2+1, n/2+2,...n-1}) = fft(x_{i=0, 2, 4, ...x_{n-2}}) - w_n^i fft(x_{i=1, 3, 5...n-1})
$$

# Lưu ý về kỹ thuật cài đặt

## Chuẩn hóa bậc đa thức

## Đệ quy

## Khử đệ quy

## Bài tập ví dụ: POST2-VOJ

# Bài tập luyện tập
- [VOJ POST2](http://vn.spoj.com/problems/POST2/)
- [FFT problems on Codeforces](http://codeforces.com/problemset/tags/fft)
- [FFT problems by a2oj.com](https://a2oj.com/Category.jsp?ID=42)

# Tài liệu tham khảo
- [1] Rohit Thummalapalli. Fourier Transform: Nature’s Way of Analyzing Data. *Yale Scientific*, 2010. [Link](http://www.yalescientific.org/2010/12/fourier-transform-natures-way-of-analyzing-data/)
- [2] Alejandro Dominguez. Highlights in the History of the Fourier Transform. IEEE Pulse, 2016. [Link](http://pulse.embs.org/january-2016/highlights-in-the-history-of-the-fourier-transform/) 
- [3] Stefan Woerner. Fast Fourier Transform. *Numerical Analysis Seminar*, Swiss Federal Institute of Technology Zurich, 2008. [Link](http://www2.math.ethz.ch/education/bachelor/seminars/fs2008/nas/woerner.pdf)
- [4] Fortnow and Homer. A Short History of Computational Complexity. *Bulletin of the European
Association for Theoretical Computer Science 80*, June 2003. [Link](http://people.cs.uchicago.edu/~fortnow/beatcs/column80.pdf)
- [Bài toán nhân đa thức, phép biến đổi Fourier nhanh trên csstudyfun.wordpress.com (có chứng minh các tính chất được đề cập trong bài](https://csstudyfun.wordpress.com/2009/01/12/bai-toan-nhan-da-thuc-phep-bien-doi-fourier-nhanh-fast-fourier-transform-fft/)
- [Bài giảng của trường DH Aalto, Phần Lan](https://drive.google.com/open?id=0BxCwa-q7x3eWT3ZfakNHMWVveTg) 
- [Code cài đặt của e-maxx](http://e-maxx.ru/algo/fft_multiply)
- ["Tutorial on FFT — The tough made simple." trên Codeforces](http://codeforces.com/blog/entry/43499)