# Contributing to Super Sonic X (ssX)

---

## Welcome, Fellow Jester

Welcome to the ssX project. Before you submit your first contribution, please read this document carefully. We have specific requirements to ensure all code represents genuine human labor and intellectual contribution.

---

## Our Philosophy

The ssX project stands for:
- **Human sovereignty** over automated mediocrity
- **Code as labor** — every line represents human thought
- **Community over corporation** — we build for ourselves, not the Archons
- **Quality over speed** — we'd rather have one well-crafted patch than ten AI-generated hallucinations

---

## What We Accept

We welcome contributions from human developers who:

1. Understand the code they're modifying
2. Can explain the **why** behind their changes, not just the **what**
3. Are willing to engage in technical discussion about their patches
4. Respect the project's philosophical stance on human authorship

---

## Transparency Disclosure Requirement

**Effective immediately:** All contributors must disclose their tool usage in every pull request and commit message.

### Required Disclosure Format

When submitting contributions, you MUST include one of the following disclosure statements in your commit message or PR description:

#### For Pure Human Work:
```
Authored-by: Human contributor <email>
Tool-disclosure: None. All code written by human hand and mind.
Sole-responsibility: I take full responsibility for the logic and security of this contribution.
```

#### For AI-Assisted Work (Augmented Coding - Permitted):
```
Authored-by: Human contributor <email>
Tool-disclosure: AI used for [spell-checking/suggestions/documentation aid/refactoring assistance]
Augmentation-type: Human-verified, human-refactored, human-validated
Sole-responsibility: I take full responsibility for the logic and security of this contribution.
I affirm that:
- The primary architectural decisions were made by me
- The logic flow was designed by me, not the AI
- I have verified the code works as intended
- I understand every function and its side effects
```

#### For AI-Generated Code (Prohibited - Do NOT Submit):
```
DO NOT SUBMIT - This appears to be raw AI output without human verification.
```

### What Constitutes "AI-Assisted" vs. "AI-Generated"

#### PERMITTED: Augmented Coding (Human-Driven)

The following are acceptable uses of AI tools:

- **Spell-checking and grammar assistance** for documentation
- **Suggesting** alternative implementations (which you evaluate and choose)
- **Refactoring existing code** you've already written (AI reorganizes, you verify)
- **Generating unit tests** for code you've written
- **Documentation assistance** (outlines, grammar fixes)
- **Finding typos** in your manually-written code

**Key requirement:** You must be able to explain every line of code as if you wrote it yourself. The AI suggested; you decided.

#### PROHIBITED: Generative Output (AI-Driven)

The following are NOT acceptable:

- Pasting AI-generated code without understanding it
- Submitting code where the AI made the primary architectural decisions
- Using AI to "explain" code you didn't write
- Bulk-generating functions or modules without human design
- Submitting code you cannot defend in a code review

**Key prohibition:** If you cannot pass a code review where you explain the **why** of every function, do not submit it.

---

## Structural Modification Threshold

To be accepted, contributions must demonstrate **human authorship** through:

### 1. Meaningful Commit Messages

Bad: `fix bug` or `AI refactor`
Good: `Fix XServer crash in ProcXInputDeviceInit when device is NULL - Race condition in hotplug handler caused use-after-free. Verified crash reproduces with attached test.`

### 2. Comments That Explain "Why"

Every non-obvious code change must include a comment explaining the reasoning:

```c
/* Why: Previous implementation allowed NULL pointer dereference when 
 * XInput devices were hot-unplugged during initialization. This was
 * a latent bug since the XFree86 4.3 era, only触发ed when device was
 * removed within 50ms of insertion. Added NULL check per the Xorg security
 * guidelines in SECURITY.md */
```

NOT acceptable:
```c
/* Fixed bug in hotplug
```

### 3. Code Review Defense

Be prepared to answer:

- **Why** did you choose this approach?
- **What** alternatives did you consider and reject?
- **How** does this affect the security model?
- **What** tests did you run to verify correctness?

If you cannot answer these questions, your contribution may be rejected.

---

## Code Style Requirements

- Follow the existing code style in the file you're modifying
- Use meaningful variable names (no `x`, `foo`, `temp` unless genuinely temporary)
- Keep functions under 200 lines
- Add comments for non-obvious logic

---

## Security Considerations

All contributors must:

1. **Never** introduce known vulnerable patterns (see CWE-89, CWE-416, etc.)
2. **Always** validate input from untrusted sources
3. **Report** security vulnerabilities to maintainers privately first
4. **Understand** the X11 security model before modifying input handlers

---

## How to Submit a Contribution

1. **Fork** the repository
2. **Create** a feature branch: `git checkout -b my-feature`
3. **Make** your changes with proper disclosure
4. **Test** locally (include test cases)
5. **Commit** with disclosure in message
6. **Submit** a Pull Request with:
   - Description of what changed
   - Why it changed that way
   - Tool disclosure statement
   - Security impact assessment (if any)

---

## Rejection Criteria

Contributions may be rejected if they:

1. Appear to be raw AI output without human verification
2. Lack meaningful comments explaining design decisions
3. Introduce security vulnerabilities
4. Break existing functionality without justification
5. Fail to include required tool disclosure

---

## Questions?

If you're unsure whether your contribution meets these standards, open an issue or contact the maintainers before starting serious work.

---

*The Jesterman guards the quality.*
*The Fool protects the craft.*
*Human hands write this code.*

---

*This document is supplemental to the LICENSE and CODE_OF_SOVEREIGNTY.md.*
*Last amended: AI-Assisted Policy v1.0*