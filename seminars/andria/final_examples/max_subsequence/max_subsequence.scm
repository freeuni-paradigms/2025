(define (max-subsequence a b)
  ;; IMPLEMENT
  -1)




;; max-subsequence ფუნქციის ტესტები
(display "Testing max-subsequence")(newline)
(display (if (equal? 3 (max-subsequence '(1 2 3 4 5) '(1 7 3 9 5 10))) "max-subsequence: 1 SUCCESS" "max-subsequence: 1 FAILURE"))(newline)
(display (if (equal? 4 (max-subsequence '(1 2 3 4 5) '(1 3 2 3 5))) "max-subsequence: 2 SUCCESS" "max-subsequence: 2 FAILURE"))(newline)
(display (if (equal? 4 (max-subsequence '(1 2 3 2 4) '(1 5 3 2 4))) "max-subsequence: 3 SUCCESS" "max-subsequence: 3 FAILURE"))(newline)
(display (if (equal? 0 (max-subsequence '(1 2 3 2 4 5 6 7 8 9 10) '(101 102 103 104 105 106 107 108 109 110))) "max-subsequence: 4 SUCCESS" "max-subsequence: 4 FAILURE"))(newline)
(display (if (equal? 5 (max-subsequence '(5 1 6 3 10 7 4 2 8 9) '(3 4 10 2 6 5 1 8 9 7))) "max-subsequence: 5 SUCCESS" "max-subsequence: 5 FAILURE"))(newline)
(display (if (equal? 6 (max-subsequence '(3 1 5 6 4 10 2 7 8 9) '(4 9 1 3 5 8 6 10 2 7))) "max-subsequence: 6 SUCCESS" "max-subsequence: 6 FAILURE"))(newline)
(display (if (equal? 5 (max-subsequence '(6 9 3 5 1 4 2 8 7 10) '(5 2 10 3 6 9 1 8 7 4))) "max-subsequence: 7 SUCCESS" "max-subsequence: 7 FAILURE"))(newline)
(display (if (equal? 4 (max-subsequence '(9 4 10 3 5 6 2 8 7 1) '(4 1 8 7 3 6 9 10 5 2))) "max-subsequence: 8 SUCCESS" "max-subsequence: 8 FAILURE"))(newline)
(display (if (equal? 10 (max-subsequence '(1 2 3 4 5 6 7 8 9 10) '(1 2 3 4 5 6 7 8 9 10))) "max-subsequence: 9 SUCCESS" "max-subsequence: 9 FAILURE"))(newline)

