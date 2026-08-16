---
title: Hướng dẫn viết bài trên VNOI Wiki
description: 
published: true
date: 2026-08-16T04:54:50.473Z
tags: 
editor: markdown
dateCreated: 2026-08-16T04:54:50.473Z
---

# Hướng dẫn viết bài trên VNOI Wiki (mới)

Đây là tài liệu mô tả các yêu cầu và tiêu chuẩn bài viết của VNOI Wiki, được áp dụng cho các bài viết của team tình nguyện viên hoặc các bài viết đóng góp đến từ quý tác giả cho dự án VNOI Wiki, Tạp chí VNOI,…

## Yêu cầu chung

Bài viết cần được viết dưới dạng tập tin [markdown](https://www.markdownguide.org/), khuyến khích sử dụng công cụ [HackMD](https://homepage.hackmd.io/) để thuận tiện cho việc chia sẻ tập tin và các giai đoạn hiệu đính bài viết.

## Trình bày

### Công thức toán học

Toàn bộ các biến, công thức hay ký hiệu toán học cần được trình bày dưới dạng LaTeX bằng cách thêm hai ký tự `$` vào đầu và cuối đoạn văn bản cần sử dụng LaTeX. Đối với các công thức dài cần được trình bày trên một dòng riêng biệt, ta dùng `$$`. Ví dụ:

```
Phi hàm Euler của một số nguyên dương $n$ là số lượng số bé hơn hoặc bằng $n$ và nguyên tố cùng nhau với $n$, được kí hiệu là $\varphi(n)$ hoặc $\phi(n)$. Công thức tính phi hàm Euler là:

$$
\varphi(n) = \prod_{1 \leq i \leq k} p_i^{q_i - 1} \cdot (p_i - 1) = n \cdot \prod_{1 \leq i \leq k} \left( 1 - \frac{1}{p_i} \right)
$$
```

Quý tác giả có thể tham khảo [ashki github](https://ashki23.github.io/markdown-latex.html), hoặc [hướng dẫn LaTeX](https://www.overleaf.com/learn) (do trang Overleaf biên soạn), hoặc [tổng hợp ký hiệu LaTeX](https://drive.google.com/file/d/1dOgQ4T3o585reXvZr7Y6YqU7wVKyhnaD/view?usp=sharing) để hiểu rõ hơn về cách sử dụng công cụ này.

#### Các cú pháp cơ bản

- **Phép nhân:** Sử dụng `\cdot` hoặc `\times`, không sử dụng `*`.
- **Phép chia:** Sử dụng `\divi` hoặc `\ratio` hoặc phân số `\frac{...}{...}`, không sử dụng `/`. Có thể sử dụng `\displaystyle` để ép hiển thị phân số cỡ lớn đối với inline LaTeX.
- **Dấu ba chấm:** Sử dụng `\dots` hoặc `\cdots`, không sử dụng `...`.
- **Phép mũ:** Sử dụng `10^{12}`, không sử dụng `1e12`.
- **Ngoặc:** Nên sử dụng `\left` và `\right` để tự động điều chỉnh kích thước ngoặc.
    - Cách trình bày đúng `\left( \frac{a}{b} \right)`, kết quả hiển thị là $\displaystyle\left( \frac{a}{b} \right)$.
    - Cách trình bày sai `( \frac{a}{b} )`, kết quả hiển thị là $\displaystyle(\frac{a}{b})$

#### Sử dụng hàm

Khi sử dụng các hàm thông dụng, ta cần thêm dấu `\` ở trước, ví dụ `$\max a_i$` chứ không phải `$max a_i$`. Đối với các hàm không được định nghĩa sẵn trong LaTeX, ta sử dụng `\operatorname{...}` hoặc `\mathrm{...}`. Ví dụ:

```
$$
\mathrm{lcm}(a, b) = \frac{a \times b}{\gcd(a, b)}
$$
```

#### Các thống nhất về ký hiệu khác (tùy chọn)

Để đảm bảo sự đồng bộ về mặt ký hiệu đối với các bài viết của VNOI, chúng mình khuyến khích quý tác giả tuân theo các thống nhất về ký hiệu như sau:

- Sử dụng `\mathcal{O}` thay vì `O` khi mô tả độ phức tạp, kết quả hiển thị là $\mathcal{O}$.
- Đối với các tên biến có trên hai ký tự được đặt tên theo thuật toán, sử dụng `\texttt{...}` để phân biệt với tên biến toán học (đối với toán học, chỉ có các ký hiệu đặc biệt như vi phân $dx$ mới sử dụng hai ký tự trở lên cho một tên biến). Ví dụ `\texttt{solve}(i, j)`, kết quả hiển thị là $\texttt{solve}(i, j)$.

### Ảnh minh họa

Chúng mình khuyến khích quý tác giả sử dụng ảnh minh họa để hỗ trợ các việc diễn giải bằng chữ, giúp tăng độ dễ hiểu và sinh động cho bài viết. Gợi ý một số công cụ vẽ hình:

- Giao diện: Adobe Illustrator, PowerPoint, MS Paint,...
- Code: Thư viện manim (Python), LaTeX, Typst,...
- Vẽ sơ đồ: draw.io,...

Trong trường hợp quý tác giả gặp khó khăn trong việc vẽ hình, có thể liên hệ team Wiki để hỗ trợ trong quá trình hiệu đính bài viết.

Để hạn chế việc lấy ảnh của một trang web đã bị sập, quý tác giả nên tải ảnh đó về và upload lên bài viết ở HackMD. Trong trường hợp, ảnh/video có độ phân giải cao, hãy đính kèm link drive chứa ảnh/video đó khi gửi bài viết.

### Các tính năng markdown khác

- Gán đường link: Để gán đường link, sử dụng cú pháp `[nội dung](đường link)`.
- Block `spoiler`: Sử dụng cho các phần chứng minh dài không đóng góp trực tiếp vào vấn đề đang đề cập, các gợi ý không muốn cho người đọc xem ngay,...

```markdown=
:::spoiler Tựa đề
Nội dung ở đây
:::
```

:::spoiler Tựa đề
Nội dung ở đây
:::

- Các block `warning`, `success` và `danger`:

```markdown=
:::warning
Critical content demanding immediate user attention due to potential risks.
:::

:::success
Crucial information necessary for users to succeed.
:::

:::danger
Negative potential consequences of an action.
:::
```

:::warning
Critical content demanding immediate user attention due to potential risks.
:::

:::success
Crucial information necessary for users to succeed.
:::

:::danger
Negative potential consequences of an action.
:::

- Các block `[!NOTE]`, `[!TIP]`, `[!IMPORTANT]`, `[!WARNING]`, `[!CAUTION]`:

```markdown=
> [!NOTE]  
> Highlights information that users should take into account, even when skimming.

> [!TIP]
> Optional information to help a user be more successful.

> [!IMPORTANT]  
> Crucial information necessary for users to succeed.

> [!WARNING]  
> Critical content demanding immediate user attention due to potential risks.

> [!CAUTION]
> Negative potential consequences of an action.
```

> [!NOTE]  
> Highlights information that users should take into account, even when skimming.

> [!TIP]
> Optional information to help a user be more successful.

> [!IMPORTANT]  
> Crucial information necessary for users to succeed.

> [!WARNING]  
> Critical content demanding immediate user attention due to potential risks.

> [!CAUTION]
> Negative potential consequences of an action.


## Nội dung

### Cấu trúc

Một bài viết học thuật thuộc VNOI Wiki thông thường có cấu trúc như sau:

```markdown
# Tựa đề

<!-- Giới thiệu tác giả, reviewer(s) -->
<!-- Mục lục -->

## Giới thiệu

## Mục lý thuyết 1

## Mục lý thuyết 1

## ...

## Ứng dụng / Bài tập ứng dụng

## Phụ lục / Tham khảo
```

### Tài liệu tham khảo

Đối với các bài viết có dạng dịch thuật hoặc bài viết nguyên bản của tác giả nhưng có tham khảo các nguồn tài liệu có sẵn, cần thêm nguồn và trích dẫn cụ thể ở đầu (đối với bài viết dịch thuật) hoặc cuối (đối với bài viết nguyên bản). Các trường hợp bị tính là “đạo văn” sẽ không được duyệt bài.

## Mã nguồn

Các phần mã nguồn trực tiếp trong văn bản cần được đưa vào hai ký tự `` ` `` ở đầu và cuối. Đối với các mã nguồn xuất ở như một block riêng biệt, sử dụng:

````markdown
```cpp=
// Code ở đây
```
````

Có thể thay thế `cpp` thành ngôn ngữ tương ứng và tùy chỉnh kiểu hiển thị đánh số dòng (`=` nếu muốn hiển thị đánh số dòng, `!` nếu không muốn hiển thị).

### Các yêu cầu về mã nguồn

- Không sử dụng `#define int long long`.
- Không khuyến khích sử dụng `define`, `typedef`; nên ghi rõ từ khóa trong mã nguồn.
- Trong trường hợp cần nhóm nhiều biến, nên sử dụng `struct` thay vì `pair`, `tuple` hay `array`.
- Các hằng số nên được viết dưới dạng `const` thay vì `#define`.
- Các tên hàm/struct/class nên có nghĩa và nghĩa này nên thể hiện một phần hàm này hoặc sử dụng tên riêng của hàm/thuật toán tương ứng nếu có. 
### Các thống nhất về format mã nguồn

Nhằm đảm bảo tính học thuật và giáo dục cao cho các bài viết thuộc VNOI Wiki và các dự án học thuật liên quan của VNOI, các mã nguồn mẫu/tham khảo được đưa vào bài viết cần đảm bảo một số thống nhất cơ bản sau:

- Tên biến nên được đặt dựa trên tiếng Anh, ví dụ `counter` hoặc `cnt` thay vì `dem`.
- Sử dụng tên biến/hàm nhiều từ theo kiểu `camelCase` (viết hoa đầu mỗi từ, không bao gồm từ đầu tiên), ví dụ `calculateDepth`.
- Sử dụng tên class/struct nhiều từ theo kiểu `CamelCase` (viết hoa đầu mỗi từ, bao gồm từ đầu tiên), ví dụ `GraphNode`.
- Mã nguồn cần được chia hàm rõ ràng, nếu có thể, chỉ đưa các hàm cần thiết vào phần mã nguồn mẫu/tham khảo.
- Khuyến khích sử dụng comment (bằng Tiếng Việt) cho các đoạn code dài hoặc/và khó hiểu.
- Đối với các mã nguồn dài, có thể đưa vào `spoiler` như sau:

````markdown
:::spoiler Code tham khảo
```cpp=
// Code ở đây
```
:::
````

- Lưu ý, đối với các mã giả (pseudocode), ta sử dụng format của python.