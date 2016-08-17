# Hướng dẫn cho contributor

# Đăng ký làm contributor

Để đăng ký làm contributor, các bạn có thể gửi tin nhắn cho [RR](https://www.facebook.com/Nguyen.RR), nói rõ muốn làm VNOI Contributor. Sau đấy các bạn sẽ được add vào group Facebook "VNOI Contributor" và có thể làm tiếp theo hướng dẫn.

Thông thường các contributor sẽ phải nộp 1 file markdown để giới thiệu bản thân và làm quen với việc viết markdown.

# Tạo bài viết mới

Các bài viết trên VNOI có cấu trúc [hình cây](http://vnoi.info/contributor/fileview). Các bạn nhìn qua để hiểu cần cho bài viết của mình vào đâu.

Để tạo bài mới, click vào New, gõ path của file có đủ dấu `/`, ví dụ: `/translate/topcoder/Ten-bai-viet`. Chú ý bạn **KHÔNG** được dùng tiếng Việt có dấu.

- Các bài là dịch thuần túy cho vào `/translate`.

**Chú ý**: Path của file dùng để tạo link, do đó bạn không nên thay đổi tên bài viết sau khi bài viết đã hoàn thành. Vì vậy hãy chọn tên bài viết hợp lý.

# Viết markdown

Tất cả các bài viết trên VNOI được viết theo định dạng markdown. Bạn có thể xem ví dụ [[ở đây|markdown]]. Bạn có thể click vào Edit để xem code markdown.

Mình khuyến khích dùng Atom editor cho việc viết markdown.

Để up ảnh, bạn có thể dùng editor trên VNOI và kéo thả ảnh vào. Chú ý rằng tên file ảnh sẽ là tên file ảnh trong máy của bạn, nên trước khi up ảnh lên, bạn nên đổi tên ảnh thành "ten_bai_viet_ten_anh" để tránh bị trùng tên với những người khác (trong trường hợp trùng tên ảnh sẽ không hiển thị đúng).

Một vài chú ý:

- Link bài viết khác trên wiki: `[[chữ hiển thị|link/sau/contributor]]`. Chú ý bạn không nên đặt absolute link (kiểu http://vnoi.info/contributor/...), và chú ý là chỉ có contributor mới vào đc link `vnoi.info/contributor`.
- Link thông thường: `[chữ hiển thị](https://link.com)`
- Để đặt tên bài viết, thêm 1 dòng `# Tiêu đề` ở đầu bài viết.
- Các heading luôn dùng từ heading 1: `#`, không nhảy cóc. Như vậy thì Table of content mới hiện đúng.
- Công thức toán cho vào dấu `$$`. Các biến, đoạn code ngắn cho vào trong 2 dấu *`*.

# Quản lý bài viết

Tất cả các bài viết được quản lý bằng [Trello](https://trello.com/). Do đó bạn cần có 1 account trello. Trong board VNOI articles, bạn sẽ thấy trạng thái của tất cả các bài viết. Một bài viết là một task và sẽ trải qua các trạng thái:

- TODO: Chưa ai dịch
- Doing: Đang dịch
- Review: Đang review
- Review 2: Đang review lần 2
- Done: Bài viết đã hoàn thành

Nếu bạn nhận dịch / viết bài nào, thì tự assign mình vào task đó, set deadline, comment link bài dịch trên VNOI. Sau đó bạn chuyển task qua cột tương ứng:

- Nếu bạn nhận dịch, chuyển sang cột Doing
- Nếu bạn dịch xong, chuyển sang cột Review
- Nếu bạn nhận review, sau khi review xong chuyển sang cột Review 2.

Tip:

- Ấn `q` để chỉ hiện những task của mình.