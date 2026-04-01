# Super Sonic X: The X Server for Super Sonic Freedom

**Super Sonic X** is a high-performance, hardened fork of the final **XFree86** lineage. This project exists to reclaim the desktop from GPU-centric corporate churn and return it to the users of embedded systems, retro hardware, and lean workstations.

We are restoring the classic 2D rendering pipeline and preserving **XAA (XFree86 Acceleration Architecture)** as a primary engine not a "legacy" feature marked for deletion.



### The "Red Wedding" of Xorg
In 2009, the mainstream X development path underwent a radical shift led by **Redhat** interests. This was lead by **Dave Arlin** you can see his name at the top of every code file he helped mangle in the license of most headers/code from this era. They fundamentally trashed the architecture by dismantling drivers into slower, external modules to force the EXA/Glamor pipeline.
This broken model destroys the compiler's ability to use full static Link Time Optimization (LTO). By relying on dynamic "crap loaders" they introduced unnecessary latency and memory fragmentation, literally frustrating the CPU cache and causing stability issues in memory-heavy applications like Minecraft. It is more work to repair that damage than it is to use a cleaner tree. Super Sonic X reverts this by returning to a fully static, integrated server model.

---

### Resisting "Boiling the Frog" our Digital Rights are Eroding
A display server should draw windows, not act as a surveillance agent. We are seeing a push for OS-level gatekeeping, such as display protocols passing identity tokens or reading /etc/age to comply with government surveillance masquerading as "age verification."
We refuse to let the sovereign computing dream die. Super Sonic X will never implement telemetry or identity-tracking mechanisms. Your hardware shouldn't report to a central authority just to draw a window.

---

### The NetBSD Foundation
This project is built upon the monumental, often-overlooked work of the **NetBSD Project**. While the mainstream Linux ecosystem abandoned XFree86 in the mid-2000s, the NetBSD developers maintained, secured, and refined this codebase within their `xsrc` tree. 

Super Sonic X is an enshrining of that work. We recognize NetBSD as the final, true stewards of the XFree86 architecture. Without their decade of "quiet" maintenance, this codebase would have been lost to bit-rot. **We carry their torch forward.**

---

### Standing on the Shoulders of Giants
This fork is a tribute to the hackers who did the real work in the trenches:
* **The NetBSD `xsrc` Maintainers:** For keeping the fire burning.
* **Alan Coopersmith & Adam Jackson + Friends:** For the architectural brilliance that defined the X11 era.
* **The Original XFree86 Team:** For building the foundation that still outperforms modern "composed" stacks on real-world 2D hardware.

---

### The Mission
* **No Corporate Bureaucracy:** We don't answer to Corporate. We answer to the hardware.
* **Technical Merit First:** We are working to recover the 1,800+ abandoned PRs left to rot in corporate-managed organizations due to rigid CoC enforcement and merge freezes. We do not resist contributors.
* **Static & Fast:** We prioritize fully static builds that CPU caches love, eliminating the dynamic overhead that adds lag.
* **XAA Restoration:** Bringing back first-class acceleration for chips that don't do "Glamor."
* **Lean & Mean:** If a feature requires a massive dependency tree just to draw a window, it doesn't belong here.

---

### Repository Info
* **Upstream:** XFree86 4.x via NetBSD `xsrc`
* **Focus:** 2D Acceleration, Stability, and Low-Latency Input.
* **Contribution:** Send us clean code. We value technical merit and hardware support over "Contributor Covenants" and corporate boilerplate BS
* **Contact:** https://t.me/supersonicxdev
