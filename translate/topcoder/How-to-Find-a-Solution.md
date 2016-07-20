# How to Find a Solution
(Đang dịch ...)
Nguồn: [Topcoder](https://www.topcoder.com/community/data-science/data-science-tutorials/how-to-find-a-solution/)

## Giới thiệu ##

Với nhiều bài toán trên topcoder (TC), lời giải có thể được tìm ra dễ dàng ngay khi đọc xong đề bài. Điều này có được là do những nét tương đồng giữa những bài toán có lời giải giống nhau. Những nét tương đồng này chính là những gợi ý tuyệt vời cho những coder kinh nghiệm để có thể nhận định được những bài toán. Mục tiêu chính của bài viết này là hướng dẫn để người đọc cũng có thể nhận định được chúng.

### Những bài toán không yêu cầu kĩ năng đặc biệt (mô phỏng, tìm kiếm, sắp xếp, ...) ###

Hầu hết các trường hợp, những bài toán này thường chỉ yêu cầu bạn thực thi từng bước một với những công việc rất dễ. Ràng buộc thì không quá lớn cũng không quá nhỏ. Và những bài này thường là bài đầu tiên (bài dễ nhất) trong TC SRM. Chúng thường để kiểm tra xem bạn code nhanh và chính xác như nào, và không yêu cầu kiến thức về thuật toán.

Hầu hết các bài toàn sẽ yêu cầu bạn mô phỏng tất cả các bước được nêu ra trong đề. 

> [BusinessTasks](https://community.topcoder.com/stat?c=problem_statement&pm=1585&rd=6535) - SRM 236 Div 1:
> 	Có N nhiệm vụ được liệt kê dưới dạng 1 vòng tròn, nhiệm vụ đầu tiên kề với nhiệm vụ cuối cùng. Cho một số n. Bắt đầu từ nhiệm vụ đầu tiên, di chuyển theo chiều kim đồng hồ (từ thứ 1 đến thứ 2 rồi tiếp tục như vậy) và đồng thời đếm từ 1 đến n. Khi đếm đến n, bỏ nhiệm vụ hiện tại ra khỏi danh sách và đếm từ nhiệm vụ tiếp theo. Lặp lại thủ tục này cho đến khi chỉ còn 1 nhiệm vụ. Return nhiệm vụ đó.

Với N <= 1000 bài này chỉ là vấn đề của code, không có thuật toán gì đặc biệt - thực hiện từng bước một cho đến khi chỉ có lại một nhiệm vụ. Những loại bài toán này thường có N nhỏ, vậy nên không cần phải quan tâm đến trường hợp N với thuật toán phức tạp. Cần nhớ rằng trong topcoder thì 100 triệu phép tính vẫn có thể chạy được. 

Loại bài này cũng có những bài cần một chút tìm kiếm 

> [TallPeople](http://community.topcoder.com/stat?c=problem_statement&pm=2923&rd=5854) - SRM 208 Div 1:
> Có một nhóm người được xếp thành một ma trận R x C, R hàng, C cột. Nhiệm vụ của bạn là trả về 2 số - Số thứ nhất là chiều cao của người cao nhất trong những người thấp nhất ở mỗi hàng, số thứ hai là chiều cao của người thấp nhất trong những người cao nhất ở mỗi cột.

Như bạn có thể thấy, đây là một bài toán tìm kiếm rất đơn giản. Bạn chỉ cần theo các bước được mô tả trong đề và tìm ra 2 giá trị yêu cầu. Những bài TC khác có thể yêu cầu sắp xếp các bộ theo quy luật nào đó. Những bài như vậy có thể trong những dạng bài này, vì chúng quá dễ hiểu - chỉ sắp xếp! Bạn có thể làm với thuật toán sort O(N^2) hoặc sử dụng các thư viên có sẵn. 
	 
** Ví dụ khác: **

[MedalTable](http://community.topcoder.com/stat?c=problem_statement&pm=2922&rd=5855) - SRM 209 Div 1 

### Tìm kiếm theo chiều rộng (Breadth First Search - BFS) ###

Những bài sử dụng BFS thường yêu cầu tìm số bước ít nhất (hoặc đường đi ngắn nhất) từ 1 điểm đầu đến điểm cuối. Bên cạnh đó, đường đi giữa 2 điểm bất kì thường có chung trọng số (và thường là 1). Phổ biến nhất là dạng bài cho bảng NxM, có những ô đi qua được và những ô không đi qua được. Bảng này có thể là mê cung, sơ đồ, các thành phố hoặc các thứ các thứ tương đương. Có thể nói đây là những bài toàn BFS kinh điển (classic). Bởi vì độ phức tạp của BFS là tuyên tính trong hầu hết các trường hợp (N^2 hoặc NlogN), giới hạn của N (hoặc M) có thể lớn, lên tới 1 triệu.

> [SmartWordToy](http://community.topcoder.com/stat?c=problem_statement&pm=3935&rd=6532) - SRM 233 Div 1:
> Cho một từ gồm 4 chữ cái Latin in thường. Với một lần click bạn có thể đổi bất kì chữ nào thành chữ cái trước hoặc sau nó trong bảng chữ cái (ví dụ 'c' có thể thành 'b' hoặc 'd'). Bảng chữ cái sẽ theo chu kì vòng lặp, tức là 'a' có thể thành 'z' và 'z' có thể thành 'a'.
> 
> Cho một tập các rằng buộc, mỗi rằng buộc sẽ là tập các từ bị cấm. Một rằng buộc bao gồm 4 xâu kí tự. Một từ gọi là bị cấm nếu mỗi chữ cái của nó đều xuất hiện trong chính ràng buộc ở vị trí đó, i.e. chữ đầu tiên ở trong xâu đầu tiên, chữ thứ 2 trong xâu thứ 2, ... Ví dụ, có rằng buộc sau "lf a tc e" thì các từ sau bị cấm "late", "fate", "lace" và "face".
> 
> Bạn cần phải tìm số lần bấm nút nhỏ nhất để từ ban đầu biến thành từ đích mà không đi qua từ cấm, hoặc trả về -1 nếu không thể biến được.

** Gợi ý: **
	
- Coi các từ là các trạng thái. Có nhiều nhất 26^4 từ khác nhau gồm 4 chữ cái.
- Có nhiều cách để biến một trạng thái để một trạng thái khác.
- Chi phí để biến đổi 1 trạng thái luôn là 1 (với 1 lần click)
- Bạn cần phải tìm số bước nhỏ nhất để đến được trạng thái địch từ trạng thái ban đầu.

Mọi thứ đều chỉ ra rằng bài này cần giải bằng BFS. Những điều tương tự như trên sẽ thường thấy trong các bài BFS. Bây giờ, chúng ta cùng xem một BFS bài khá thú vị.

> [CaptureThemAll](http://community.topcoder.com/stat?c=problem_statement&pm=2915&rd=5853) - SRM 207 Div 2 (3rd problem):
> Harry đang chơi cờ vua. Anh có một quân mã, còn đối thủ là Joe có 1 quân hậu và 1 quân xe. Hãy tìm số bước nhỏ nhất để quân mã phải đi để ăn được cả hậu và xe.

** Gợi ý: ** Mới đầu, có vẻ như bài này là 1 bài quy hoạch động hoặc backtrack. Nhưng nếu để ý kĩ đề bài, ta sẽ có những nhận xét sau:

- Đề cho 1 bảng.
- Quân mã có thể đi từ 1 ô tới các ô mà nó có thể đi được.
- Chi phí ở mỗi bước đi là 1.
- Bạn cần tìm số bước đi nhỏ nhất.

Với những thông tin trên, ta có thể dễ dàng giải được bằng BFS. Đừng bối rối nếu những điểm liên thông là những ô không kề nhau. Hãy nghĩ những mỗi ô là một điểm trên đồ thị hay một trạng thái hay bất cứ cái gì bạn muốn.

Chú ý rằng phần lớn những gợi ý về thuật giải BFS là chi phí bằng 1 cho mỗi bước.

Bạn có thể luyện tập thêm về BFS bằng những ví dụ sau:

** Ví dụ khác: **

[RevolvingDoors](http://community.topcoder.com/stat?c=problem_statement&pm=3064&rd=5869) - SRM 233 Div 1

[WalkingHome](http://community.topcoder.com/stat?c=problem_statement&pm=3444&rd=5868) - SRM 222 Div 1

[TurntableService](http://community.topcoder.com/stat?c=problem_statement&pm=3117&rd=5865) - SRM 219 Div 1

### Loang (Flood Fill) ###

Thỉnh thoảng bạn sẽ gặp phải bài toán cần tới loang, một kĩ thuật sử dụng BFS để tìm tất cả các điểm có thể đi tới. Điểm khác biết giữa so với những bài BFS ở trên là bạn không phải tìm chi phí nhỏ nhất.

Ví dụ, có một mê cung, ô 1 là không đi được và 0 là đi được. Ban cần phải tìm tất cả các ô mà có thể đi đến từ ô góc trái trên. Bài này chỉ cần lấy ra một đỉnh đã thăm, nhét tất cả các đỉnh chưa thăm mà kề với đỉnh hiện tại vào queue rồi tiếp tục làm như vậy cho đến khi queue rỗng. Lưu ý rằng hầu hết trường hợp DFS (Depth First Search) sẽ không thể chạy được vì sẽ bị tràn stack. Tốt hơn hết là nên dùng BFS. Đây là một bài ví dụ:

[grafixMask](http://community.topcoder.com/stat?c=problem_statement&pm=2998&rd=5857) - SRM 211 Div 1: 
