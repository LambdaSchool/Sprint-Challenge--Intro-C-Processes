**1. List all of the main states a process may be in at any point in time on a standard Unix system. Briefly explain what each of these states means.**

-   Created - This is where the process is first created. It will then sit at ready.
-   Ready - This can also be called waiting. All this is that is is ready and waiting to be excuted, so it is sitting in the memory.
-   Running - This is where the process has been excuted and now it is running the process.
-   Blocked - This is where the process cannot carry on with its excution and gets stopped.
-   Terminated - This is where the process gets destroyed either after the end of running or it is explicitly killed.

**2. What is a zombie process?**

-   A zombie process is where the parent does not clean the child after they have both been executed.

**3. How does a zombie process get created? How does one get destroyed?**

-   A zombie process can be created when there is not a wait on the parent process. So the parent will end up not cleaning the child. For it to be destroyed, there is a reaper process that will check if processes are running and if not, it will destroy it.

**4. What are some of the benefits of working in a compiled language versus a non-compiled language? More specifically, what benefits are there to be had from taking the extra time to compile our code?**
The benefits of compiling the code is that it will be faster to excute the process. This is really helpful for data hevy applications because it will allow quicker run times ove a non-compiled language.
