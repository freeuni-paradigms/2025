(define (reverseDup l)
  (let ((rev (reverse l)))
    (append rev rev)
  )
)

;                     a ^ b =
;b % 2 == 0   ret     a ^ (b/2) * a ^ (b/2)
;            else a * a ^ (b/2) * a ^ (b/2)

(define (binpow a b)
  (if (= b 0) 1
      (let ((bp (binpow a (div b 2))))
        (if (= 0 (remainder b 2)) (* bp bp)
          (* a bp bp)
        )
      )
  )
)

(define (fib-helper a b n)
  (if (zero? n) a
    (fib-helper b (+ a b) (- n 1))
  )
)

(define (fib_ n)
  (fib-helper 0 1 n)
)

(define (fib__ n)
  (let loop ((a 0) (b 1) (i 0))
    (if (= i n) a
      (loop b (+ a b) (+ i 1))
    )
  )
)

(define (fib n)
  (letrec (
           (fibrec (lambda (a b i)
                      (if (= i n) a (fibrec b (+ a b) (+ i 1))))
                   )
           )
    (fibrec 0 1 0)   
  )
)

(define (partition n l)
  (if (null? l) '(()())
    (let ((pt (partition n (cdr l))))
      (if (< (car l) n)
        (list (cons (car l) (car pt)) (cadr pt)) 
        (list (car pt) (cons (car l) (cadr pt)))
      )
    )
  )
)

(define (count e l)
  (apply + (map (lambda (x) (if (= e x) 1 0)) l))
)

(define (permutation? l1 l2)
  (if (not (= (length l1) (length l2))) #f
    (zero? (apply + (map (lambda (e) (if (= (count e l2) (count e l1)) 0 1)) l1)))
  )
)

(define (is-way-helper graph a b visited)
  (cond ((= a b) 1)
        ((> (count a visited) 0) 0)
        (else 
          (apply +
            (map (lambda (e)
                        (cond ((= (car e) a) (is-way-helper graph (cadr e) b (cons a visited)))
                              ((= (cadr e) a) (is-way-helper graph (car e) b (cons a visited)))
                              (else 0)
                        )
                     )
            graph)
          )
        )
  )      
)

(define (isWay? graph a b)
  (let ((ans (is-way-helper graph a b '())))
      (> ans 0)
  )
)


