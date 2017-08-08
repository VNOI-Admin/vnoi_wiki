# Skip Lists

**Tác giả**: Vũ *chipchip* Phúc Hoàng

A: *"Mày AC bài Z kiểu gì thế? Tao dùng set không được."*  
B: *"Dễ mà mày, tao code Splay thôi. 400 dòng 20 phút ez gg."*  
A: *"-_-"*

Câu chuyện thật tưởng như đùa trên cũng không phải là hiếm gặp. Splay Tree (hay nói rộng hơn, Balanced Binary Search Tree) là một cấu trúc dữ liệu toàn năng có thể giải quyết rất nhiều bài toán, tuy nhiên nó cũng là một thứ đáng khiếp sợ đối với dân competitive programmers vì độ khó code của nó. Trong một contest với áp lực thời gian căng thẳng, chẳng mấy ai dám code Balanced Binary Search Tree và còn đảm bảo code không bị bug nữa. Tuy nhiên, bạn không thể hoàn toàn tránh được nó, vẫn có những bài mà những thư viện có sẵn như std::set hay những cấu trúc đơn giản như Segment Tree, Fenwick Tree không thể giải được, và bạn vẫn phải nhờ cậy đến Splay Tree trong nỗi tuyệt vọng.

May mắn thay, dân competitive programmers đã tìm ra cách sử dụng Skip Lists như một sự thay thế hoàn hảo cho Balanced Binary Search Tree. Skip Lists với ý tưởng hết sức đơn giản dễ nhớ, cộng thêm với khả năng tùy biến tuyệt vời đã làm xua tan đi nỗi sợ code khó bug nhiều (trừ khi bạn có trình độ Da xua thượng thừa như nhân vật B trong đoạn hội thoại trên; trong trường hợp đó, bạn có thể bỏ qua bài viết này). Bài viết này sẽ giới thiệu cho các bạn những ý tưởng và cách sử dụng Skip Lists cơ bản nhất.
