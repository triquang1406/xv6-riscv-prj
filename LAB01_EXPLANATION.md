# Giải thích về Lab01

**Ngày thực hiện:** 2026-02-24 07:55:55  
**Người thực hiện:** ofdquantum  

## Phần 1: wc

Phần này thực hiện chức năng đếm số từ, số dòng, và số ký tự trong một tập tin. Chương trình lấy tên tập tin từ dòng lệnh và sau đó đọc nội dung của tập tin để thực hiện việc đếm. Kết quả được in ra màn hình. Đây là một công cụ hữu ích để phân tích nội dung tập tin.

## Phần 2: cat

Phần này yêu cầu đọc và hiển thị nội dung của tập tin lên màn hình. Đây là một phần hỗ trợ người dùng để xem nhanh nội dung của một tập tin mà không cần mở bằng một trình soạn thảo. Chương trình sẽ nhận đường dẫn tập tin từ đầu vào và xuất ra nội dung.

## Phần 3: getprocs syscall

Syscall này cho phép người dùng lấy thông tin về các tiến trình đang chạy trong hệ thống. Khi gọi syscall này, các thông tin như PID, tên tiến trình, và trạng thái của tiến trình sẽ được thu thập và trả về cho người gọi. Việc sử dụng syscall này giúp tăng cường khả năng giám sát và quản lý hệ thống.

## Phần 4: trace syscall

Trace syscall là một công cụ cho phép theo dõi hoạt động của các tiến trình trong hệ thống. Khi được kích hoạt, syscall này sẽ ghi lại các thông tin quan trọng về hoạt động của tiến trình, chẳng hạn như các syscall được gọi và thời gian gọi. Điều này rất hữu ích cho việc phát hiện và khắc phục sự cố trong ứng dụng và hệ thống.

---  

Trên đây là các chi tiết về Lab01, bao gồm cả bốn phần chức năng mà chúng tôi đã thực hiện để hiểu rõ hơn về kiến trúc và hoạt động của hệ điều hành.