Tác giả: Vũ Trọng Quang

(Nguồn: https://www.stdio.vn/articles/giai-thuat-cat-tia-alpha-beta-564)

Giải thuật cắt tỉa Alpha-beta cực kỳ quan trọng khi lập trình các trò chơi như cờ vua hay cờ tướng, khi các không gian trạng thái của những trò chơi này có độ phức tạp cao. Cắt tỉa Alpha-beta sẽ giúp loại bỏ những không gian trạng thái không cần thiết và hỗ trợ tối ưu hóa thuật toán tìm kiếm Minimax.

## Giới thiệu

Giải thuật cắt tỉa Alpha-beta từng được nhiều nhà khoa học máy tính đề xuất ý tưởng và không ngừng được cải tiến cho đến ngày nay. Giải thuật này thường sử dụng chung với thuật toán tìm kiếm Minimax nhằm hỗ trợ giảm bớt các không gian trạng thái trong cây trò chơi, giúp thuật toán Minimax có thể tìm kiếm sâu và nhanh hơn. Giải thuật cắt tỉa Alpha-beta có nguyên tắc đơn giản "Nếu biết là trường hợp xáu thì không cần phải xét thêm".

## Tiền đề bài viết
Trong thời gian tìm hiểu và thực thi thuật toán Minimax, nguồn tài liệu của STDIO luôn là ưu tiên tìm kiếm đầu tiên của tôi. Trong lúc thực hiện việc tối ưu thuật toán, các tài liệu nói về Minimax đều nói về thuật toán cắt tỉa Alpha-beta và đây là động lực để tôi viết bài viết này nhằm giúp hoàn thiện phần còn lại của bài viết [Giải Thuật Tìm Kiếm Minimax](https://www.stdio.vn/articles/read/283/giai-thuat-tim-kiem-minimax) trên STDIO.

Đây cũng là lời cảm ơn đến anh [La Kiến Vinh](https://www.stdio.vn/users/index/1/la-kien-vinh), người thầy đã mang lại nhiều cảm hứng và ấn tượng cho tôi.

## Đối tượng hướng đến
Bài viết dành cho các bạn đã vững lập trình và có kiến thức về các giải thuật tìm kiếm. Bài viết cũng yêu cầu bạn đọc xem qua Giải Thuật Tìm Kiếm Minimax trước khi tiếp tục.

## Giải thuật cắt tỉa Alpha-beta
### Chiến lược cắt tỉa
Nút Max có một giá trị alpha (lớn hơn hoặc bằng alpha – luôn tăng), nút min có một giá trị beta (nhỏ hơn hoặc bằng beta – luôn giảm).

Khi chưa có alpha và beta xác định thì thực hiện tìm kiếm sâu (depth-first) để xác định được alpha, beta, và truyền ngược lên các nút cha.

### Cắt tỉa như thế nào?
Một số sách và tài liệu có đề cập với việc cắt tỉa alpha và cắt tỉa beta, ở đây tôi cũng sẽ nói về việc đó và dùng một cách khác đó là dùng các khoảng trong toán học. Hãy nhìn cây trò chơi phía dưới để hình dung cách để cắt tỉa.

![cay_tro_choi](https://www.stdio.vn/statics/external_data/files/pages/articles/2017/564/content/cay_tro_choi.png)

Chắc hẳn những bạn đang đọc bài này sẽ đều thắc mắc vấn đề tại sao chúng ta có thể cắt bỏ toàn bộ những nút con của C trên cây trò chơi trên.

Đầu tiên là xét cây từ trái sang phải ta sẽ thấy S là Max, theo chiến lược đưa ra vậy chúng ta sẽ có giá trị alpha ≥ 10 tại S.

Tiếp theo, ở C ở đây là nút Min (trạng thái trò chơi dành cho Max) tức là sẽ lấy giá trị nhỏ nhất của các nút con ở dưới. Nếu như vậy thì giá trị chúng ta phải lấy là beta ≤ 3.

Sau khi xác định được alpha và beta, chúng ta có thể dễ dàng xác định việc có cắt tỉa hay không. Ở nút S (Max), giá trị alpha luôn ≥ 10 (luôn tăng) nhưng ở C (Min) thì giá trị luôn luôn ≤ 3 (luôn giảm), nên việc xét các con còn lại ở C là không cần thiết.

Nếu nói theo khoảng thì hiện tại chúng ta chỉ nhận khoảng ≥ 10 tại nút gốc  S, vậy thì đâu cần bận tâm đến việc khoảng ≤ 3 tại nút C.

Ví dụ với một cây trò chơi trung bình
![cay_tro_choi_2](https://www.stdio.vn/statics/external_data/files/pages/articles/2017/564/content/cay_tro_choi_2.png)

Ở đây chúng ta cũng xét từ trái qua phải bắt đầu từ nút gốc và nút con bên trái sẽ được ưu tiên duyệt trước. Duyệt nguyên cây này sẽ khá dài dòng nhưng để bạn hiểu tôi sẽ viết ra các bước sau.

Xét duyệt từ trên gốc xuống sâu (vì ban đầu chưa hề tồn tại giá trị alpha hay beta của các nút). Nút đầu tiên ta duyệt là E sẽ gặp giá trị 2 (alpha ≥ 2), khi đó ở trên chưa có giá trị beta để ta có thể so sánh nên sẽ bắt đầu duyệt con tiếp theo của nút E đó và ở đây ta sẽ chọn cho alpha = 3 (Max).

Lưu ý là chúng ta luôn luôn duyệt từ trái sang phải và phải lần lượt từng nhánh một, sau đó sang nhánh tiếp theo cùng gốc. Vậy nên tiếp theo chúng ta sẽ đưa giá trị alpha này lên nút B (Min) và nút B – beta ≤ 3, sau đó nút F sẽ được duyệt, và ta phải tìm alpha của F.  Khi duyệt con đầu tiên mang giá trị 5 vậy alpha của F – alpha ≥ 5.

Tại B – beta ≤ 3 và tại F – alpha ≥ 5. Như vậy chúng ta không cần xem xét các nút con còn lại của F vì cái ta cần ở đây chỉ là khoảng ≤ 3 nên ta cắt toàn bộ các con còn lại.

Sau khi duyệt toàn bộ các con của B thì tại B – beta = 3, và tại nút A – alpha ≥ 3.

Các bạn tự duyệt phần còn lại nhé. Đừng lo lắng, nếu không hiểu có thể đọc lại vài lần hoặc có thể comment, mình sẽ giải đáp giúp các bạn.

## [Trò chơi giải trí với AI hay](https://play.google.com/store/apps/dev?id=8454869713871668206)

-   [Cờ Carô với AI hay](http://play.google.com/store/apps/details?id=com.popoko.gomokuvn)
-   [Cờ Vua với AI hay](http://play.google.com/store/apps/details?id=com.popoko.chessru)
-   [Cờ Gomoku với AI hay](http://play.google.com/store/apps/details?id=com.popoko.gomokukr)
-   [Trò chơi Dò Mìn](http://play.google.com/store/apps/details?id=com.popoko.minesweeper)

## Lời kết
Bài viết đã khái quát về lý thuyết việc cắt tỉa alpha-beta, còn việc hiện thực nó trong code như thế nào thì có thể mình sẽ dành một bài viết sau bao gồm mã giả và cả cách hiện thực bằng Python 2.7.

Một số thuật ngữ hoặc kiến thức chưa chính xác mong các bạn chỉ bảo giúp mình vì khả năng mình cũng hơi kém chỉ mong có thể giúp mọi người có cảm hứng cùng học, cùng hiểu và cùng đam mê.

## Tham khảo
PDF về Minimax và cắt tỉa Alpha-beta:
http://staff.agu.edu.vn/nvhoa/AI/lecture4.pdf - 10/05/2017