---
title: Một số Tài liệu hay về Thuật Toán
description: 
published: true
date: 2026-03-30T15:31:11.620Z
tags: 
editor: markdown
dateCreated: 2023-12-25T10:59:45.760Z
---

# Một số Tài liệu hay về Thuật Toán

Có một điều đặc biệt của việc học Lập trình thi đấu, mà lại rất hiếm có ở nhiều môn học khác, đó là tài liệu Lập trình thi đấu **gần như luôn sẵn có**. Thậm chí, nếu chỉ xét phạm vi kiến thức trong chương trình Trung học phổ thông, thì những nguồn tài liệu miễn phí đã có thể đáp ứng được hầu hết các nhu cầu học tập của người học.

Tuy nhiên, vì nguồn tài liệu Lập trình thi đấu là rất rộng và đa dạng, những người học mới rất dễ gặp phải tình trạng tiếp cận Lập trình thi đấu mà không có định hướng cụ thể, điều này khiến cho quá trình khám phá bộ môn này trở nên rắc rối và khó khăn.

Trong bài viết này, đội ngũ VNOI Wiki sẽ giới thiệu đến bạn đọc những nguồn tài liệu hay và chất lượng về Thuật toán, bao gồm cả những nguồn tài liệu do CLB Olympic Tin học Việt Nam (VNOI) xây dựng và những nguồn tài liệu khác. Để bạn đọc tiện lợi hơn trong việc lựa chọn nguồn tài liệu, các tài liệu sẽ chia thành các phần như sau:

- Tài liệu lý thuyết thuật toán.
- Tài liệu & bộ đề luyện tập.
- Tài liệu tra cứu cú pháp, mã nguồn.
- Tài liệu về các tối ưu liên quan đến phần cứng.

## Lựa chọn ngôn ngữ lập trình

Trước khi bắt đầu với nội dung chính của bài viết, chúng mình sẽ dành ra một phần nhỏ để bàn luận về ngôn ngữ lập trình, là công cụ trung gian giúp các lập trình viên chuyển hóa ý tưởng thuật toán thành lệnh máy mà máy tính có thể hiểu được.

Việc lựa chọn ngôn ngữ lập trình cho bộ môn Lập trình thi đấu như thế nào, nhìn chung, không có ảnh hưởng quá nhiều đến quá trình xây dựng tư duy, tiếp thu kiến thức về thuật toán của người học. Tuy nhiên, với đặc thù của môi trường thi đấu, một số ngôn ngữ lập trình cụ thể sẽ đáp ứng nhu cầu của bộ môn này tốt hơn. Trong Lập trình thi đấu, những ngôn ngữ lập trình phổ biến bao gồm C/C++, Python, Java, Pascal, Kotlin,...

Một lưu ý dành cho các bạn học sinh có mong muốn theo đuổi Chuyên Tin đó là ở Việt Nam, các kì thi chính thức (Tuyển sinh, Học sinh giỏi các cấp, Olympic Tin học,...) đều có máy chấm hỗ trợ ngôn ngữ C/C++ và Pascal. Ngoài ra, một số cuộc thi cho phép thí sinh sử dụng Python.

Việc chọn ngôn ngữ lập trình để học Lập trình thi đấu là tùy vào người học, tuy nhiên, trong đa số các tài liệu ngày nay, ngôn ngữ C/C++ là ngôn ngữ chiếm ưu thế. Thật vậy, nếu nhìn vào [thống kê về ngôn ngữ lập trình được sử dụng](https://www.go-hero.net/jam/17/languages) qua các vòng tại Google CodeJam 2017 - một cuộc thi Lập trình thi đấu hàng đầu do Google tổ chức, ta có thể thấy sự phổ biến của C/C++ so với các ngôn ngữ khác như sau:

| Ngôn ngữ | Vòng loại | Vòng 1A | Vòng 2 | Vòng 3 | Chung kết |
| :-: | :-: | :-: | :-: | :-: | :-: |
| C++ | 12047 | 2982 | 1935 | 303 | 22 |
| Python | 5899 | 894 | 287 | 32 | 8 |
| Java | 5117 | 736 | 183 | 32 | 6 |
| C | 888 | 88 | 17 | 0 | 0 |
| C# | 806 | 111 | 39 | 5 | 0 |

*Thống kê 5 ngôn ngữ lập trình phổ biến nhất Google CodeJam 2017*

Sự phổ biến của C/C++ trong Lập trình thi đấu là vì bản thân ngôn ngữ lập trình này được sinh ra để tối ưu hiệu suất của chương trình cả về khía cạnh thời gian và bộ nhớ. Ngoài ra, thư viện chuẩn của C++ cũng hỗ trợ các hàm và cấu trúc dữ liệu cơ bản cần thiết, tiện lợi cho việc cài đặt các chương trình trong khuôn khổ Lập trình thi đấu. Do đó, C++ là lựa chọn được khuyến khích khi bắt đầu với bộ môn này.

Trong bài viết này, đa số các tài liệu được chúng mình gợi ý cũng sẽ được minh họa bằng mã nguồn được viết bằng C++. Nếu đang sử dụng một ngôn ngữ lập trình khác, bạn đọc vẫn hoàn toàn có thể theo dõi chúng một cách bình thường.

Ngoài ra, nếu bạn đọc là người mới bắt đầu, trang [Learn C++](https://www.learncpp.com/) sẽ là một nguồn tài liệu tự học phù hợp, giải thích chi tiết các từ khóa và hàm/cấu trúc dữ liệu được sử dụng trong C++.

## Tài liệu lý thuyết về thuật toán

### Sách: Tài liệu giáo khoa Chuyên Tin

- **Nhóm tác giả:** Thầy Hồ Sĩ Đàm, Thầy Đỗ Đức Đông, Thầy Lê Minh Hoàng, Thầy Nguyễn Thanh Hùng.
- **Ngôn ngữ lập trình:** Pascal.
- **Giới thiệu sơ lược:** *Tài liệu giáo khoa Chuyên Tin* là bộ sách về Lập trình thi đấu do NXB Giáo dục Việt Nam ban hành và được biên soạn bởi những giáo viên Chuyên Tin kì cựu. Các nội dung được đề cập trong tài liệu bám sát với chương trình Chuyên Tin cho các lớp chuyên 10, 11, 12 do Bộ giáo dục và Đào tạo ban hành.

:::spoiler Tải tài liệu
- [Tài liệu giáo khoa Chuyên Tin, quyển 1](https://drive.google.com/file/d/0BwcTB8a10LBweWxNcExnVzF5dG8/view?usp=sharing&resourcekey=0-WKR6p7r5Djmi--uvQnT-pg)
- [Tài liệu giáo khoa Chuyên Tin, quyển 2](https://drive.google.com/file/d/0BwcTB8a10LBwY2kzV0dTMEhYb0E/view?usp=sharing&resourcekey=0-jwmNe4E3bBtidsboHXQPSA)
- [Tài liệu giáo khoa Chuyên Tin, quyển 3 (tập 1)](https://drive.google.com/file/d/0BwcTB8a10LBwTFBGREdfbnNFYXM/view?usp=sharing&resourcekey=0-xVwjQFoXV4OFwpoVHWywyg)
- [Tài liệu giáo khoa Chuyên Tin, quyển 3 (tập 2)](https://drive.google.com/file/d/1c1dQaNG5XAZWGo3oTA_4mGwubG3LRqni/view?usp=sharing)
:::

### [Sách: Giải thuật & Lập trình](https://drive.google.com/file/d/0BwcTB8a10LBwV1J3T2xDTGhQNmM/view?usp=sharing&resourcekey=0-R4tnYInPWCKb5W_DK_JQwQ)

- **Tác giả:** Thầy Lê Minh Hoàng.
- **Ngôn ngữ lập trình:** Pascal.
- **Giới thiệu sơ lược:** Sách *Giải thuật & Lập trình* cũng là tài liệu giáo khoa về Tin học vốn rất thân thuộc với nhiều thế hệ học sinh Chuyên Tin. Sách chứa đựng nhiều chủ đề Lập trình thi đấu từ cơ bản đến nâng cao như quay lui, sắp xếp, quy hoạch động, đồ thị,...

### [VNOI Wiki](https://wiki.vnoi.info/)

- **Tác giả:** CLB Tin học Việt Nam (VNOI).
- **Ngôn ngữ lập trình:** C++.
- **Giới thiệu sơ lược:** VNOI Wiki là dự án wiki lớn nhất Việt Nam được thực hiện bởi cộng đồng Olympic Tin học Việt Nam và các tình nguyên viên tham gia VNOI qua các nhiệm kỳ. Bạn đọc có thể tìm các bài viết đa dạng chủ đề từ nhập môn đến các kiến thức rất khó, được biên soạn và hiệu đính kỹ càng bởi đội ngũ VNOI Wiki.

### [VNOI Roadmap](https://roadmap.sh/r/vnoi-roadmap)

- **Tác giả:** CLB Tin học Việt Nam (VNOI).
- **Ngôn ngữ lập trình:** C++.
- **Giới thiệu sơ lược:** VNOI Roadmap là một lộ trình hoàn chỉnh bao gồm các chủ đề được đánh giá độ khó từ 1 đến 5 sao, dành cho mọi đối tượng từ học sinh đến sinh viên, đặc biệt là các bạn mới bắt đầu tiếp xúc với Tin học.

### Sách: Guide to Competitive Programming / Competitive Programmer's Handbook

- **Tác giả:** [Antti Laaksonen](https://www.cs.helsinki.fi/u/ahslaaks/).
- **Ngôn ngữ lập trình:** C++.
- **Giới thiệu sơ lược:** Nếu có thể thành thạo kỹ năng đọc tiếng Anh, quyển *Guide to Competitive Programming* hoặc *Competitive Programmer's Handbook* sẽ là một lựa chọn vô cùng phù hợp để bắt đầu với Lập trình thi đấu. Cả hai quyển sách có nội dung khá tương đương và đều bám sát với ICPC và các kì thi Olympic Tin học các cấp.

:::spoiler Tải tài liệu
- [Guide to Competitive Programming](https://drive.google.com/file/d/1-V14oys49VJM6oipdcaIGcLzakaR_Hkn/view?usp=sharing)
- [Competitive Programmer's Handbook](https://cses.fi/book/book.pdf)
- Bạn đọc cũng có thể tìm mua bản cứng của sách "Guide to Competitive Programming" qua nền tảng [Springer](https://link.springer.com/book/10.1007/978-3-031-61794-2) hoặc [Amazon](https://www.amazon.com/Guide-Competitive-Programming-Algorithms-Undergraduate-dp-3031617932/dp/3031617932/)
:::

### [USACO Guide](https://usaco.guide/)

- **Tác giả:** Đội tuyển Tin học Quốc gia Mỹ và nhiều tác giả khác.
- **Ngôn ngữ lập trình:** C++.
- **Giới thiệu sơ lược:** *USACO Guide* cùng với trang chấm bài trực tuyến [USACO](https://usaco.org/) là nền tảng tài liệu và bài tập Lập trình thi đấu được xây dựng bởi Đội tuyển Tin học Quốc gia Mỹ. Các chủ đề được phân loại theo các cấp độ (General, Bronze, Silver,...) kèm theo các tính năng hỗ trợ người dùng theo dõi tiến độ luyện tập vô cùng hữu ích. Hầu hết các bài viết trên nền tảng USACO Guide đều đi kèm một danh sách các bài tập chất lượng để luyện tập với chủ đề vừa được học.

### [CP-Algorithms](https://cp-algorithms.com/)

- **Tác giả:** Nhiều tác giả.
- **Ngôn ngữ lập trình:** C++.
- **Giới thiệu sơ lược:** *CP-Algorithms* là dự án mã nguồn mở, đăng tải tài liệu Lập trình thi đấu được dịch lại từ trang https://e-maxx.ru/algo từ Tiếng Nga sang Tiếng Anh. Các bài viết trên trang CP-Algorithms được đóng góp bởi nhiều tác giả có kinh nghiệm Lập trình thi đấu lâu năm.

### [The Ultimate Topic List](https://youkn0wwho.academy/topic-list)

- **Tác giả:** Shahjalal "YouKn0wWho" Shohag.
- **Giới thiệu sơ lược:** *The Ultimate Topic List* là danh sách các chủ đề Lập trình thi đấu có tác giả là người đã có nhiều năm kinh nghiệm trong bộ môn, tham gia nhiều kì thi lớn ở cấp độ quốc tế và đã giúp đỡ nhiều bạn trẻ trong việc theo đuổi Lập trình thi đấu. Trang web bao gồm các chủ đề được phân loại theo độ khó, từ Nhập môn đến các chủ đề rất hiếm trong các kì thi, được chia thành các mục tương ứng để tiện theo dõi.

### [Sách: Handbook of Geometry for Competitive Programmers](https://victorlecomte.com/cp-geo.pdf)

- **Tác giả:** Victor Lecomte.
- **Ngôn ngữ lập trình:** C++.
- **Giới thiệu sơ lược:** Giống như cái tên, *Handbook of Geometry for Competitive Programmers* là tài liệu lập trình tập trung vào các chủ đề hình học tính toán trên không gian hai và ba chiều. Tài liệu bao quát các kiến thức hình học tính toán cơ bản với nhiều hình ảnh minh họa, giúp người đọc xây dựng nền tảng kiến thức hình học vững chắc để giải quyết các bài toán Lập trình thi đấu.

### Các tài liệu khác

- [Channel guide của anh Phạm Văn Hạnh](https://docs.google.com/spreadsheets/d/1bOfb3m5P641p0pcXen9CAZSCkLvIXD3VUl8QbYEv4NQ/edit?usp=sharing): Nguồn tổng hợp các tài liệu Lập trình thi đấu theo chủ đề, kèm video hướng dẫn chi tiết tại kênh YouTube của anh.
- [Một số vấn đề đáng chú ý trong môn Tin học](https://drive.google.com/file/d/0BwcTB8a10LBwZHh0c3p0M2NqZ1E/view?usp=sharing&resourcekey=0-sGBMwRWJQF0-oV27ula5Mg): Cuốn sách được viết bởi các cựu học sinh trường chuyên Phan Bội Châu - Nghệ An. Bạn đọc có thể tìm đọc các chủ đề ít được đề cập trong nhiều tài liệu giáo khoa như duyệt ưu tiên, thuật toán tìm kiếm chuỗi KMP, quy hoạch động trạng thái, quy hoạch động vị trí cấu hình, quy hoạch động trên cây, tô màu đồ thị, thuật toán Dijkstra với đỉnh ảo,...
- [KC Book (Quyển 1)](https://drive.google.com/file/d/0B6O77opfHxDDV1lxdF9jWHVUZDA/view?usp=sharing&resourcekey=0-bLURXsP9BNX7O6W1izMEjQ): Tài liệu giới thiệu nhiều kỹ thuật thú vị thường gặp trong các bài toán Lập trình thi đấu như các thuật toán duyệt, xử lý bit, quy hoạch động,...
- [KC Book (Quyển 3)](https://drive.google.com/file/d/0BwcTB8a10LBwSmZFdGhSY1lMNVU/view?usp=sharing&resourcekey=0-POIEScAwD22aQFyr2mBfaw): Tương tự quyển 1, KC Book quyển 3 giới thiệu các kỹ thuật Lập trình thi đấu và được chia thành 3 phần: Quy hoạch động, Cấu trúc dữ liệu và Đồ thị.
- [Bản dịch Introduction to Algorithm](https://drive.google.com/file/d/0B2B4YFwy4LhWWl9NV2pyQno1S0U/view?resourcekey=0-soNqn2omBd1JNaDUZSsh5g): Tài liệu giáo khoa chất lượng, giới thiệu đầy đủ và chi tiết các chủ đề về Giải thuật và Cấu trúc dữ liệu nói chung. Đội ngũ VNOI Wiki xin cảm ơn bạn Nguyễn Văn Khởi đã chia sẻ link.

## Tài liệu & bộ đề luyện tập

### [VNOJ Educational Contests](https://oj.vnoi.info/contests/?search=educational) và [VOI Revision](https://oj.vnoi.info/contests/?search=voi+revision)

- **Tác giả:** CLB Tin học Việt Nam (VNOI).
- **Giới thiệu sơ lược:** *VNOJ Educational Contests* và *VOI Revision* là chuỗi các contest chất lượng được tổ chức theo chủ đề do đội ngũ Tình nguyện viên VNOI thực hiện qua các năm nhằm hướng đến các bạn học sinh Chuyên Tin có định hướng tham gia các kì thi Học sinh giỏi cấp tỉnh/thành phố và Học sinh giỏi Quốc gia. Các contest được trải rộng trên các chủ đề Quy hoạch động, Cấu trúc dữ liệu, Nhân ma trận, Truy vấn trên cây, Chia căn,...

### [CSES Problemset](https://cses.fi/problemset/)

- **Tác giả:** Antti Laaksonen.
- **Giới thiệu sơ lược:** *CSES Problemset* là bộ bài tập chất lượng đi kèm với bộ sách *Guide to Competitive Programming / Competitive Programmer's Handbook* do cùng tác giả biên soạn. Các bài tập được phân chia theo các chủ đề (Introductory Problems, Sorting and Searching, Dynamic Programming,...). CSES Problemset chủ yếu tập trung vào các bài tập kinh điển, đề bài ngắn gọn, giúp bạn đọc xây dựng nền tảng lập trình vững chắc trước khi bước vào các kì thi lớn.

### [Library Checker](https://judge.yosupo.jp/)

- **Tác giả:** Kohei "Yosupo" Morita.
- **Giới thiệu sơ lược:** *Library Checker* là nền tảng tập trung vào các bài tập Lập trình thi đấu kinh điển. Đúng như cái tên, nền tảng này được sinh ra với mục đích chính là để kiểm tra tính đúng đắn, độ hiệu quả của các mã nguồn được dùng làm thư viện, template, [ICPC Team Reference Document (TRD)](https://euc.icpc.global/home-2024/trd-instructions/),...

### [OI Checklist](https://checklist.spoi.org.in/home)

- **Tác giả:** Ẩn danh.
- **Giới thiệu sơ lược:** *OI Checklist* là trang tổng hợp các đề thi Olympic Tin học của các quốc gia/khu vực có phong trào Lập trình thi đấu phát triển như INOI, JOI/JOISC, NOI, CNOI, POI, EGOI, EJOI, IZhO, BKOI, APIO, IOI,... Trang web hỗ trợ tính năng đánh dấu để tiện lợi cho việc theo dõi tiến độ luyện tập, rất phù hợp cho các bạn đọc đang có mục tiêu tham dự các kì thi Olympic Tin học từ Học sinh giỏi Quốc gia trở lên.

### Online Judges

Ngoài ra, bạn đọc còn có thể tìm các nguồn bài tập Lập trình trên các nền tảng chấm bài tự động (còn gọi là Online Judge hay OJ) phổ biến như [VNOJ](https://oj.vnoi.info/), [Codeforces](https://codeforces.com/), [AtCoder](https://atcoder.jp/),... và rất nhiều nền tảng OJ khác.

## Tài liệu tra cứu cú pháp, mã nguồn

### [cppreference](https://en.cppreference.com/w/)

- **Tác giả:** Nhiều tác giả.
- **Giới thiệu sơ lược:** Tài liệu giới thiệu tất cả các từ khóa, hàm, cấu trúc dữ liệu,... xuất hiện trong ngôn ngữ C/C++. Bạn đọc cũng có thể sử dụng trang web này để xác định phiên bản trình biên dịch tối thiểu cần dùng cho một vài từ khóa nhất định.


### Một số thư viện mã nguồn Lập trình thi đấu nổi tiếng

- [KTH Algorithm Competition Template Library (KACTL)](https://github.com/kth-competitive-programming/kactl): Một trong những thư viện mã nguồn thi đấu phổ biến nhất được xây dựng cho các đội ICPC đến từ KTH Royal Institute of Technology.
- [NUS ICPC Team's Notebook for ACM ICPC World Final 2016](https://github.com/ngthanhtrung23/ACM_Notebook_new?tab=readme-ov-file): ICPC TRD của đội tuyển đến từ Đại học Quốc gia Singapore (NUS) gồm 3 thí sinh người Việt Nam là anh Nguyễn Hùng Tâm, Nguyễn Tấn Sỹ Nguyên và Nguyễn Thành Trung (Code cùng RR).

Bạn đọc cũng có thể tùy chỉnh ICPC TRD cho đội của chính mình bằng cách fork các Github repository trên.

## Tài liệu về các tối ưu liên quan đến phần cứng

### [Algorithms for Modern Hardware](https://en.algorithmica.org/hpc/)

- **Tác giả:** Sergey Slotin.
- **Ngôn ngữ lập trình:** C++.
- **Giới thiệu sơ lược:** Trang web cũng cấp kiến thức về High Performance Computing (HPC). Qua các bài viết, bạn đọc có thể tìm hiểu về các kỹ thuật tối ưu chương trình, bên cạnh việc tối ưu độ phức tạp thường thấy trong Lập trình thi đấu.

### [Optimization of Computer Programs in C](https://icps.u-strasbg.fr/~bastoul/local_copies/lee.html)

- **Tác giả:** Michael E. Lee.
- **Ngôn ngữ lập trình:** C.
- **Giới thiệu sơ lược:** Tương tự *Algorithm for Modern Hardware*, trang web này cũng cung cấp các tài liệu về kỹ thuật tối ưu chương trình.

<!--
**1. Giải thuật và lập trình (DSAP) - thầy Lê Minh Hoàng**


Chắc hẳn những bạn học chuyên tin đều biết đến cuốn sách này, bởi nó như là một cuốn sách giáo khoa cho chuyên tin với các kiến thức cơ bản từ quay lui, sắp xếp đến quy hoạch động, đồ thị.

[Link Download](https://drive.google.com/file/d/0BwcTB8a10LBwV1J3T2xDTGhQNmM/view?usp=sharing&resourcekey=0-R4tnYInPWCKb5W_DK_JQwQ)

**2. Tài liệu giáo khoa chuyên tin**

Về cơ bản, phần một và phần hai giống với giải thuật và lập trình, tuy nhiên được bổ sung thêm một số kiến thức như: số Catalan, xử lý số lớn bằng xâu,... Kèm theo đó là những bài tập vô cùng hấp dẫn để các bạn luyện tập.

Phần ba chứa các kiến thức nâng cao hơn, đó là hình học và lý thuyết trò chơi.

Link Download:

 - [Tập 1](https://drive.google.com/file/d/0BwcTB8a10LBweWxNcExnVzF5dG8/view?resourcekey=0-WKR6p7r5Djmi--uvQnT-pg)
 - [Tập 2](https://drive.google.com/file/d/0BwcTB8a10LBwY2kzV0dTMEhYb0E/view?usp=sharing&resourcekey=0-jwmNe4E3bBtidsboHXQPSA)
 - [Tập 3 - phần 1](https://drive.google.com/file/d/0BwcTB8a10LBwTFBGREdfbnNFYXM/view?usp=sharing&resourcekey=0-xVwjQFoXV4OFwpoVHWywyg)
 - [Tập 3 - phần 2](https://drive.google.com/file/d/1c1dQaNG5XAZWGo3oTA_4mGwubG3LRqni/view?usp=sharing)

**3. Một số vấn đề đáng chú ý trong môn tin học**

Cuốn sách này được viết bởi các cựu học sinh trường chuyên Phan Bội Châu - Nghệ An. Nó chứa các kiến thức tuyệt hay mà tài liệu giáo khoa chuyên tin hay giải thuật và lập trình đều không có như: duyệt ưu tiên, thuật toán tìm kiếm chuỗi KMP, quy hoạch động trạng thái, quy hoạch động vị trí cấu hình, quy hoạch động trên cây, tô màu đồ thị, thuật toán Dijkstra với đỉnh ảo, Interval Tree, Binary Index Tree, ...

[Link Download](https://drive.google.com/file/d/0BwcTB8a10LBwZHh0c3p0M2NqZ1E/view?usp=sharing&resourcekey=0-sGBMwRWJQF0-oV27ula5Mg)

**4. Bản dịch Introduction to Algorithm**

[Link download](https://drive.google.com/file/d/0B2B4YFwy4LhWWl9NV2pyQno1S0U/view?resourcekey=0-soNqn2omBd1JNaDUZSsh5g)

(Cảm ơn bạn Nguyễn Văn Khởi đã chia sẻ link).

**5. KC Book**

- [Quyển 1](https://drive.google.com/file/d/0B6O77opfHxDDV1lxdF9jWHVUZDA/view?usp=sharing&resourcekey=0-bLURXsP9BNX7O6W1izMEjQ)
- [Quyển 3](https://drive.google.com/file/d/0BwcTB8a10LBwSmZFdGhSY1lMNVU/view?usp=sharing&resourcekey=0-POIEScAwD22aQFyr2mBfaw)

**6. Guide To Competitive Programming**

Nếu bạn có thể đọc tiếng Anh trôi chảy, bạn có thể tham khảo quyển "Guide To Competitive Programming" được viết năm 2017. Sách sử dụng ngôn ngữ C++ và có nhiều kiến thức mới.

[Link download](https://drive.google.com/file/d/1-V14oys49VJM6oipdcaIGcLzakaR_Hkn/view?usp=sharing)
-->