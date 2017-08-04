# Hoài niệm về Pascal - Lê Minh Hoàng

Nhân chuyện thảo luận về việc IOI 2019 sẽ dừng cho phép làm bài bằng Pascal, thầy Lê Minh Hoàng đã có chia sẻ rất ý nghĩa về việc tại sao Pascal lại được giảng dạy ở Việt Nam. Để những chia sẻ của thầy không bị thất lạc mất, mình sẽ lưu lại vào đây :).

## Đầu tiên: Tại sao VN lại học Pascal?

Bây giờ có nhiều bạn chửi bới tùm lum, thậm chí cho đây là [món quà cay độc của Bộ GDDT](http://www.ddth.com/showthread.php/95997-Pascal-M%C3%B3n-qu%C3%A0-cay-%C4%91%E1%BB%99c-c%E1%BB%A7a-B%E1%BB%99-GD%C4%90T).

Không phải mình bênh Bộ GD, nhưng các bạn đó không hiểu một vấn đề lịch sử: Từ những năm 1970s, 1980s là khi tin học bắt đầu vào VN, Pascal là ngôn ngữ chính của tạp chí công nghệ PC Magazine, Turbo Pascal vẫn là best IDE, phần mềm hiệu suất cao đa số viết bằng Pascal, sách vở về thuật toán, cấu trúc dữ liệu đều dùng Pascal. Vậy ngoài Pascal ra còn có thể chọn gì khác?. Những gì Kernighan viết trong "Why Pascal Is Not My Favorite Programming Language" không hề đúng với Pascal Extension của Turbo và ObjPas sau này. Trong khi ngôn ngữ C lúc đó bị đập be bét. Lý do duy nhất nó tồn tại là vì Unix được mở mã và C được học để mổ xẻ cấu trúc Hệ điều hành mà thôi, còn cái kiểu viết C: `++(**p)***--q` thì dù bạn thành kiến cách mấy, Pascal vẫn không bao giờ cho phép viết cái code tối như thế này. Người ta nói Pascal trong sáng hơn chính là khi so sánh với C, chứ không phải so với Python hay Java là những thứ mới đâu.


## Thứ hai: Tại sao VN lại chậm chuyển sang C++?

C++ ra đời từ những năm 1980s, một ngôn ngữ sẽ cần khoảng thời gian hơn chục năm để quảng bá và kiểm chứng thực tế trước khi khẳng định nó có thể tồn tại lâu dài ít ra là trong một lĩnh vực nào đó. Đến khi họ đã kiểm chứng xong và triển khai diện rộng, sách vở tài liệu đầy đủ, cộng đồng hoạt động tích cực,... thì Việt Nam chưa có internet, nói gì đến các hình thức thương mại điện tử để mà mua sách, phần mềm, ... Ở bậc phổ thông thì kỳ thi quốc tế vẫn phổ biến Pascal cho tới đầu những năm 2000. Ở ngoài xã hội, tạp chí PC World VN ra rả các bài nói về Visual Basic, Foxpro, ... là những thứ mà các công ty tin học dùng để làm các phần mềm quản lý nhân sự,... Chẳng có bài nào nói về C++ cả. Thậm chí nhiều người đều cho là C++ là một extension của C chứ không phải là một ngôn ngữ mới nữa kia. 4 năm học khoa Toán của mình khi ra trường, CNTT có những bước phát triển nhưng là phát triển sai hướng. Mình có cảm giác là nếu như MS đánh mất vị trí #1, mọi thứ của Việt Nam sẽ reset lại như khi mình tốt nghiệp PT.


## Thứ ba: Tại sao mình phải ngừng dạy Pascal?

Pascal, Object Pascal đối với mình vẫn là ngôn ngữ hay. Thật đáng tiếc vì nó không còn sự hỗ trợ từ những ông lớn nên không được chuẩn hóa, mở rộng về ngôn ngữ cũng như thư viện hỗ trợ. Chính cái cộng đồng phát triển Free Pascal đã giết nó bằng cách đưa ra những phiên bản mới đầy lỗi, dịch sai, chậm sửa. Lẽ ra phát triển theo hướng công cụ học tập thi cử, hoàn thiện thư viện FCL-STL,... thì lại đi phát triển thêm một đống tool làm software chẳng để làm gì vì người làm chuyên nghiệp có Delphi rồi. Ngay cả mình là người code ObjPas khá giỏi mà nhiều lúc rất ức chế với mấy cái lỗi của nó, ngay cả bộ cài đặt làm cũng không nên hình.


## Thứ tư, mình khảo sát chuyện dạy C++ như thế nào?

Vào khoảng 2008-2009, có nhiều thầy khuyên và các bạn mình đề xuất chuyển sang dạy C++ ở phổ thông ở Chuyên Sư Phạm (CSP). Mình bắt đầu lộ trình dù rất nhiều bạn phê phán rất gay gắt và đề nghị chuyển ngay lập tức. Nhưng mình nắm hơi nhiều sinh mạng trong tay, không thể liều được.

- Đầu tiên là khảo sát tình hình anh em: Những đơn vị nào đang dùng C++ để học tập mô hình đó. Kết quả khá là thất vọng, chuyên Tổng Hợp (A0) có kết quả tốt nhưng đối tượng học sinh đầu vào rất khác với CSP, cách học, cách tuyển chọn cũng khác, không tham khảo được gì. Các đơn vị khác dùng C++ thì kết quả chập chờn, trong khi những đơn vị dùng Pascal như Hải Phòng, Hà Nội, PTNK... kết quả ổn định tốt.

- Tiếp theo là tìm hiểu hệ thống chấm bài thi QG (bên mình không thi thành phố nên ko quan tâm thành phố chấm kiểu gì): Kết quả: Hệ thống AMM2 không chấm được trực tiếp mã CPP, phải dịch tay, hơn nữa khi mã CPP chạy lỗi thường treo luôn hệ thống chấm... nếu không chấm tay thì phải chạy trung gian qua một code Pascal, thiệt thòi về thời gian...

- Về IDE và trình dịch: Trên Unix thì khá ổn, nhưng GCC và DevC trên Windows tính cho tới bản 3.x vẫn còn lắm lỗi quá. Sinh lỗi báo lỗi lung tung đối với người mới học sẽ gây ức chế, giảm cảm hứng tìm hiểu.

- Về tình hình học tập: Code bẩn tràn lan, vô số undefined behaviors, chẳng theo standard/style nào cả. Hệ quả của việc học tập thiếu hệ thống và không nghiêm khắc với bản thân.

- Về sách vở thì ôi thôi, bó tay luôn, xin lỗi các bộ giáo trình C++ tiếng Việt mình đã đọc qua, tất cả đều không xài được. Mình không thể yêu cầu hs đọc được tiếng Anh vì học sinh các tỉnh về CSP học đâu có nền tàng tiếng Anh tốt. Hơn nữa thứ tiếng Anh hùng biện chém gió khác hẳn với thứ tiếng Anh để đọc hiểu bản chất.

- Về nội lực: Trong bộ môn cũng toàn người như mình, nếu chuyển ngôn ngữ thì cùng chuyển chứ lệch pha thì cộng tác giảng dạy sao được. Hơn nữa C++ mình không giỏi như Pascal, dạy lập trình là phải thị phạm, không phải cứ chiếu bụp cái code lên giải thích là xong. Phải làm từ đầu => gặp bugs => debug ngay trước mũi học sinh sinh viên, nó mới học được cách thiết kế, triển khai và gỡ rối, kiểm thử. Nhỡ gặp cái bug mình gỡ cả tiết không xong thì cháy, nên hơi run.

- Về quan điểm: Có nhiều quan điểm mình không thể theo. Ví dụ nhé:
    - "Chuyển C++ chỉ là transcode thôi, if bên Pascal viết thế này bên C++ viết thế kia, while, repeat, for cũng thế...". Mình nghĩ rất khác, first language giống như tiếng mẹ đẻ, ta phải nghĩ theo ngôn ngữ đó mới được, chứ nghĩ bằng một ngôn ngữ rồi dịch ra một ngôn ngữ khác không phải là cách làm tự nhiên và hiệu quả.
    - "Dạy pointers và OOP làm gì, dạy chúng nó không hiểu mà đi thi đâu có cần". Dạy là dạy mà thi là thi, C++ vứt đi 2 thứ đó sẽ đến lúc có bài không thể giải quyết được thì biết kêu ai giờ. Mình vẫn luôn kêu ca là SGK lớp 8 dưới áp lực giảm tải vứt đi luôn lệnh REPEAT và FOR của Pascal là một sai lầm. Khó bước đầu thì mới dễ về sau, có phải vòng lặp nào viết kiểu WHILE cũng thuận với tư duy lập trình đâu.


## Thứ năm, mình triển khai dạy C++ (as first language) như thế nào?

Nói chuyện này đúng là số, chém gió tí thì gọi là thiên thời.

Cái may thứ nhất là năm 2011. Mình và thầy Đông nhận được dự án của Bộ GD viết hệ thống chấm tự động trên Windows. Mình đặt mục tiêu viết một bộ chấm ổn định, chạy không cần cấu hình cao, dịch CPP như PAS, dù ít chức năng cũng được. Mã nguồn kernel sau khi nghiệm thu Bộ giữ bản quyền, mình thì build và cập nhật bản end-user cho các nơi dùng Free. Vậy là thiên hạ khỏi băn khoăn việc dùng CPP thiệt thòi khi chấm.

Cái may thứ hai là năm 2012. UET được giao chỉnh sửa quy chế thi QG và phụ trách việc huấn luyện ĐTQG. Thầy Đàm, thầy Nghĩa, anh Việt Hà và Phạm Bảo Sơn... gọi mình với Hồ Đắc Phương đi họp, nhân lúc đó ấn luôn Code Blocks vào và thế là cái họa DevCPP với GCC cũ rích coi như được loại bỏ. Chương trình sẽ được dịch theo phiên bản mới nhất tính từ lúc triển khai kỳ thi.

Còn lại là việc nội bộ, cả bộ môn lao vào cày, học, viết giáo trình thậm chí phải thi như thật cùng bọn học sinh xem thế nào. Mình không thi được thì đi dạy thằng đi thi cũng khó. Cựu học sinh cũng phải xắn tay vào nữa.


## Cuối cùng, tại sao cứ phải Pascal/C/C++ mà không phải thứ nào khác phổ biến hơn?

Bạn có thể học một ngôn ngữ dễ hơn để làm quen với việc lập trình (Scratch, Python,...), cũng có thể dùng một ngôn ngữ khác thiết kế phần mềm (Java, Basic,...). Nhưng khi bạn muốn tìm hiểu sâu về thuật toán cũng như muốn đánh giá chính xác hiệu suất thuật toán, những ngôn ngữ đó hoàn toàn không phù hợp. Trong giai đoạn học thuật toán, ngôn ngữ lập trình, chương trình dịch, công cụ lập trình là cực kỳ quan trọng. Bởi vì bạn sẽ phải tư duy trên ngôn ngữ đó, bạn còn phải hiểu bản chất thế nào là một đoạn code tốt, thế nào là một đoạn code tồi về mặt hiệu suất. Bạn cũng không thể học các thuật toán chia để trị nếu dùng một ngôn ngữ lập trình không cho phép đệ quy, không thể đánh giá đúng hiệu suất của một thuật toán trên thực tế (đong đếm đến từng nano giây), khi mà thời gian thực hiện chương trình mất phần lớn vào công đoạn thông dịch hay kích hoạt máy ảo.

Ví dụ thế này nhé: Khi bạn học lái xe, thông thường bạn sẽ được tập bằng một chiếc sedan, hatchback hay couple. Khi ra đường phố, ngoài các loại trên bạn thường thấy phổ biến các loại xe SUV, Pick-up, roadster, ... Nhưng ở phương diện những người làm chuyên nghiệp trong ngành công nghiệp ô tô, bạn phải biết về công suất và từng chi tiết động cơ, hiểu rõ khả năng cân bằng xe, các thiết kế khí động học, độ cứng và độ bám của lốp, hệ thống phanh,... và để biết tất cả những thứ này, bạn bắt buộc phải ngồi vào một chiếc F1 dù việc điều khiển nó không hề dễ dàng và nó cũng sẽ không bao giờ là loại xe phổ biến trên đường phố.

Tất cả những thứ đó bất kỳ đơn vị nào muốn chuyển đổi có lẽ sẽ ít nhiều phải trải qua. Với một cơ chế tổ chức cồng kềnh, rất khó mà thay đổi diện rộng được nếu không nhắm mắt chịu gạch đá.

Ngay cả việc IOI có lộ trình bỏ Pascal, mình không biết gì hết vì mình không đi theo đoàn từ năm 2011 do lý do tài chính. Năm 2011 thằng Korokevich vô địch IOI bằng Pascal, chẳng ai nói gì về lộ trình này. Những năm sau cũng không thấy ai về nói hoặc một thông tư chính thức từ phía Bộ GDDT. Tất cả những xu hướng kiến thức hay thể thức mình đều phải đoán từ mấy bài tham luận của tạp chí Olympiads in Informatics.

Nói như thế tức là mình đã sử dụng hết quyền trong phạm vi có thể rồi, việc còn lại là ở cấp vĩ mô hơn nữa kia.


*Chú thích*: 1 vài nhân vật xuất hiện trong bài:

- Thầy Đông: thầy Đỗ Đức Đông.
- anh Việt Hà: thầy Nguyễn Việt Hà, HCĐ IOI lần thứ 2 năm 1990, hiệu trường ĐH Công Nghệ (UET).
- Phạm Bảo Sơn: thầy Phạm Bảo Sơn, HCB IOI năm 1994 và 1994, hiệu phó trường ĐH Công Nghệ (UET).

Các comment này được lấy từ comment của thầy Hoàng ở post của anh Trương Xuân Nam, HCB IOI 1994.