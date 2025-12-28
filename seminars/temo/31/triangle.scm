(define (row i)
  (if (= i 1) '(1)
    (let ((last (row (- i 1))))
      (map + (cons 0 last) (append last '(0)))
    )
  )
)


