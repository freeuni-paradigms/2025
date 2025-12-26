# Server Room
უნივერსიტეტის კამპუსში ახალი კომპიუტერული ლაბორატორია ემატება. ამისთვის ორი ტექნიკური გუნდი მუშაობს, hardware და software სპეციალისტები. თითოეულ მერხზე ორი ოპერაციაა ჩასატარებელი: ჯერ hardware სპეციალისტმა უნდა დადგას და ააწყოს კომპიუტერი, ხოლო შემდეგ software სპეციალისტმა დააყენოს ოპერატიული სისტემა და კურსებისთვის საჭირო პროგრამები.

## დავალების დეტალები
* თქვენ გევალებათ ამ სისტემის იმიტაციის იმპლემენტაცია ნაკადების გამოყენებით.
* მთავარი ფუნქცია, რომელიც უნდა დაწეროთ, არის SetUpServerRoom-ის იმპლემენტაცია maintenance.c ფაილში. მისი არგუმენტებია
    * int num_tables მერხების რაოდენობა ოთახში და
    * int hardware_team_size, int software_team_size თითოეული ოპერაციისთვის რამდენი სპეციალისტი იქნება.
    * ეს რიცხვები ყოველთვის მეტი იქნება 0-ზე. სხვა მხრივ, თქვენმა პროგრამამ უნდა იმუშაოს ამ არგუმენტების ნებისმიერ მნიშვნელობებზე.

* ცვლილებები მიიღება მხოლოდ maintenance.c ფაილში. ამ ფაილში, მთავარი ფუნქციის დასახმარებლად, შეგიძლიათ ნებისმიერი რაოდენობის სხვა სტრუქტურებისა და ფუნქციების შექმნა და გამოყენება. maintenance.h ფაილში არცერთი სტრაქტი არაა დამატებული, რაც თავისუფლებას გაძლევთ კოდის დიზაინში.
* ამ ორ ფაილში არ შეიძლება გლობალური ცვლადების გამოყენება. გამოიყენეთ მხოლოდ ფუნქციისადმი გადმოცემული არგუმენტები და სხვა ფუნქციებს გადაეცით მათი და ლოკალურად ფუნქციაში შექმნილი მიმთითებლები.
* შეგიძლიათ თქვენთვის დასახმარებლად შეცვალოთ სხვა ფაილები (მაგალითად, SetUpServerRoom ფუნქციის არგუმენტები tests.c ფაილში, რომ დატესტოთ პროგრამა სხვადასხვა ზომის გუნდებზე და კომპიუტერებზე). უბრალოდ გაითვალისწინეთ, რომ გასწორებისას maintenance.c ფაილის გარდა ყველა სხვა ჩანაცვლდება. 


### შეფასების კრიტერიუმები
პროგრამის სისწორეს აკონტროლებს სუპერვაიზორი, რომელსაც თითოეული ოპერაციის (hardware, software) გუნდის თითოეული წევრის შესვლა და გასვლა ოთახიდან (როდის იწყებენ მუშაობას, როდის ამთავრებენ ყველა კომპიუტერს, ...) *აუცილებლად* უნდა აცნობოთ მისი ინტერფეისის გამოყენებით, რომელსაც იხილავთ  ფაილში  supervisor.h. ამ ფუნქციების იმპლემენტაცია არ მოგეთხოვებათ (უკვე არის supervisor.c ფაილში), მხოლოდ გამოიძახეთ.
#### Hardware ჯგუფი
* void HardwareWorkerEnterRoom(int hardware_member_id); -- უნდა გამოიძახოთ ერთხელ ყოველი hardware ჯგუფის წევრისთვის როცა ის შევა ოთახში
* void HardwareWorkerStartSettingUpComputer(int hardware_member_id, int table_id); -- უნდა გამოიძახოთ ყოველ ჯერზე როცა hardware ჯგუფის წევრი დაიწყებს კომპიუტერის აწყობას
* void HardwareWorkerFinishedSettingUpComputer(int hardware_member_id, int table_id); -- უნდა გამოიძახოთ ყოველ ჯერზე როცა hardware ჯგუფის წევრი დაასრულებს კომპიუტერის აწყობას
* void HardwareWorkerLeaveRoom(int hardware_member_id); -- უნდა გამოიძახოთ ერთხელ ყოველი hardware ჯგუფის წევრისთვის როცა ის გამოვა ოთახიდან
* void AllComputerHardwareIsSetUp(int hardware_member_id); -- ბოლო hardware ჯგუფის წევრმა უნდა გამოიძახოს ერთხელ **ოთახიდან გამოსვლამდე** მას შემდეგ რაც ყველა კომპიუტერი აიწყობა
#### Software ჯგუფი
* void SoftwareWorkerEnterRoom(int software_member_id); -- უნდა გამოიძახოთ ერთხელი ყოველი software ჯგუფის წევრისთვის როცა ის შევა ოთახში
* void SoftwareWorkerStartInstallingSoftware(int software_member_id, int computer_id); -- უნდა გამოიძახოთ ყოველ ჯერზე როცა software ჯგუფის წევრი დაიწყებს აწყობილ კომპიუტერზე პროგრამების დაყენებას
* void SoftwareWorkerFinishedInstallingSoftware(int software_member_id, int computer_id); -- უნდა გამოიძახოთ ყოველ ჯერზე როცა software ჯგუფის წევრი დაასრულებს კომპიუტერზე პროგრამების დაყენებას
* void SoftwareWorkerLeaveRoom(int software_member_id);  -- უნდა გამოიძახოთ ერთხელ ყოველი software ჯგუფის წევრისთვის როცა ის გამოვა ოთახიდან
* void AllComputerSoftwareIsInstalled(int software_member_id); -- ბოლო software ჯგუფის წევრმა უნდა გამოიძახოს ერთხელ **ოთახიდან გამოსვლამდე** მას შემდეგ რაც ყველა კომპიუტერზე დაყენდება პროგრამები


თქვენთვის გადმოცემულ იმპლემენტაციაში სუპერვაიზორი უბრალოდ დაბეჭდავს მის არგუმენტებს, რაც დაგეხმარებათ პროგრამის სისწორის შემოწმებაში.

დარწმუნდით, რომ:
* თითოეული კომპიუტერისთვის ზუსტად ერთხელ ჩატარდა თითოეული ოპერაცია
* ოპერაციები მიმდევრობით კეთდება (ჯერ hardware დაყენება, შემდეგ software)
* ბოლო hardware ჯგუფის წევრმა, რომელიც ააწყობს კომპიუტერს, ოთახიდან გამოსვლამდე უნდა შეატყობინოს supervisor-ს რომ ყველა კომპიუტერი აიწყო
* ბოლო software ჯგუფის წევრმა, ორმელიც დააყენებს პროგრამებს, **ოთახიდან გამოსვლამდე** უნდა შეატყობინოს supervisor-ს რომ ყველა კომპიუტერზე დაყენდა პროგრამები

* კომპიუტერების მიმდევრობას მნიშვნელობა არ აქვს (ჯერ რომელზე დაყენდება). თუ გსურთ დააყენეთ ჯერ 1, შემდეგ 2, ან ნებისმიერი სხვა მიმდევრობით.

### ტესტირება
ფაილების კომპილაციისთვის გაუშვით **gcc supervisor.c maintenance.c tests.c -pthread**<br/>
ხოლო დაკომპილირებული ფაილის გასაშვებად: **a.exe**

### შეიძლება დაგჭირდეთ შემდეგი POSIX სტრუქტურები და ფუნქციები:
#### semaphore.h
* sem_t: სემაფორის ტიპის სტრუქტურა
* int sem_init(sem_t *sem, int pshared, unsigned int value); -- initializes the unnamed semaphore at the address pointed to by sem. The value argument specifies the initial value for the semaphore.
* int sem_destroy(sem_t *sem); -- destroys the unnamed semaphore at the address pointed to by sem.
* int sem_post(sem_t *sem); -- increments (unlocks) the semaphore pointed to by sem.  If the semaphore's value consequently becomes greater than zero, then another process or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the semaphore.
* int sem_wait(sem_t *sem); -- decrements (locks) the semaphore pointed to by sem.  If the semaphore's value is greater than zero, then the decrement proceeds, and the function returns, immediately.  If the semaphore currently has the value zero, then the call blocks until either it becomes possible to perform the decrement (i.e., the semaphore value rises above zero), or a signal handler interrupts the call.
#### pthread.h
* pthread_t: ნაკატის ტიპის სტრუქტურა
* int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); -- The pthread_create() function starts a new thread in the calling process.  The new thread starts execution by invoking start_routine(); arg is passed as the sole argument of start_routine().
* int pthread_join(pthread_t thread, void **retval); -- The pthread_join() function waits for the thread specified by thread to terminate.  If that thread has already terminated, then pthread_join() returns immediately.  The thread specified by thread must be joinable.
* void pthread_exit(void *retval); -- The pthread_exit() function terminates the calling thread and returns a value via retval that (if the thread is joinable) is available to another thread in the same process that calls pthread_join(3).
* pthread_mutex_t: მუტექსის ტიპის სტრუქტურა
* int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr); -- The pthread_mutex_init() function initialises the mutex referenced by mutex with attributes specified by attr. If attr is NULL, the default mutex attributes are used; the effect is the same as passing the address of a default mutex attributes object. Upon successful initialisation, the state of the mutex becomes initialised and unlocked.
* int pthread_mutex_destroy(pthread_mutex_t *mutex); -- The pthread_mutex_destroy() function destroys the mutex object referenced by mutex; the mutex object becomes, in effect, uninitialised. An implementation may cause pthread_mutex_destroy() to set the object referenced by mutex to an invalid value. A destroyed mutex object can be re-initialised using pthread_mutex_init(); the results of otherwise referencing the object after it has been destroyed are undefined.
* int pthread_mutex_lock(pthread_mutex_t *mutex); -- The mutex object referenced by mutex shall be locked by calling pthread_mutex_lock(). If the mutex is already locked, the calling thread shall block until the mutex becomes available. This operation shall return with the mutex object referenced by mutex in the locked state with the calling thread as its owner.
* int pthread_mutex_unlock(pthread_mutex_t *mutex); -- he pthread_mutex_unlock() function shall release the mutex object referenced by mutex. The manner in which a mutex is released is dependent upon the mutex's type attribute. If there are threads blocked on the mutex object referenced by mutex when pthread_mutex_unlock() is called, resulting in the mutex becoming available, the scheduling policy shall determine which thread shall acquire the mutex.
