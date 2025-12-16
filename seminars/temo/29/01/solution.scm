(define (reverseDup l)
  (let ((rev (reverse l)))
     (append rev rev)
  )
)

(define (binpow a b)
  (if (zero? b) 1
    (let ((bp (binpow a (div b 2))) (rem (remainder b 2)))
      (if (zero? rem)
        (* bp bp)
        (* a bp bp)
      )
    )
  )
)

;if (b % 2 == 0) -> binPow(a, b/2) * binPow(a, b/2)
;else -> a * binPow(a, b/2) * binPow(a, b/2)

(define (fib-helper a b n)
  (if (zero? n) a
    (fib-helper b (+ a b) (- n 1))
  )
)

(define (fib_ n)
  (fib-helper 0 1 n)
)

(define (fib n)
  (let fib-rec ((a 0) (b 1) (i n))
    (if (zero? i) a
      (fib-rec b (+ a b) (- i 1))
    )
  )
)
