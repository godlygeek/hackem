/* NetHack 3.6	pline.c	$NHDT-Date: 1549327495 2019/02/05 00:44:55 $  $NHDT-Branch: NetHack-3.6.2-beta01 $:$NHDT-Revision: 1.73 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2018. */
/* NetHack may be freely redistributed.  See license for details. */

#define NEED_VARARGS /* Uses ... */ /* comment line for pre-compiled headers */
#include "hack.h"

#define BIGBUFSZ (5 * BUFSZ) /* big enough to format a 4*BUFSZ string (from
                              * config file parsing) with modest decoration;
                              * result will then be truncated to BUFSZ-1 */

static unsigned pline_flags = 0;
static char prevmsg[BUFSZ];

static void FDECL(putmesg, (const char *));
static char *FDECL(You_buf, (int));
#if defined(MSGHANDLER) && (defined(POSIX_TYPES) || defined(__GNUC__))
static void FDECL(execplinehandler, (const char *));
#endif

#if defined(DUMPLOG) || defined(DUMPHTML)
/* also used in end.c */
unsigned saved_pline_index = 0; /* slot in saved_plines[] to use next */
char *saved_plines[DUMPLOG_MSG_COUNT] = { (char *) 0 };

/*Ben Collver's fixes*/
const char *
replace(const char *st, const char *orig, const char *repl)
{
    static char retval[TBUFSZ];
    char buffer[TBUFSZ];
    const char *ch, *pos;
    size_t len;
    memset(buffer, 0, TBUFSZ);
    pos = st;
    while ((ch = strstr(pos, orig))) {
        len = (ch - pos);
        strncat(buffer, pos, len);
        strncat(buffer, repl, strlen(repl));
        pos = (ch + strlen(orig));
    }
    if (pos == st) {
        return st;
    }
    if (pos < (st + strlen(st))) {
        strncat(buffer, pos, (st - pos));
    }
    strcpy(retval, buffer);
    return retval;
}

/*Ben Collver's fixes*/
const char *
piratesay(const char *orig)
{
    orig = replace(orig, "find it hard to breathe", "start dancing the hempen jig");
    orig = replace(orig, "succeed in lockin' the box", "batten down the hatches");
    orig = replace(orig, "You fall down the stairs.", "Blow the man down!");
    orig = replace(orig, "You fall down the ladder.", "Blow the man down!");
    orig = replace(orig, "You arm your fire bomb.", "Fire in the hole!");
    orig = replace(orig, "You arm your sonic bomb.", "Fire in the hole!");
    orig = replace(orig, "You arm your gas bomb.", "Fire in the hole!");
    orig = replace(orig, "move the boulder", "heave ho");
    orig = replace(orig, "no longer feel sluggish", "got your sea legs back");
    orig = replace(orig, "suddenly seems weaker", "looks seasick");
    orig = replace(orig, "don't know", "dunno");
    orig = replace(orig, " it is", " 'tis");
    orig = replace(orig, "It is ", "'Tis ");
    orig = replace(orig, "Is not ", "Ain't ");
    orig = replace(orig, "is not ", "ain't ");
    orig = replace(orig, "wipe off", "swab");
    orig = replace(orig, "wiped off", "swabbed");
    orig = replace(orig, "You", "Ye");
    orig = replace(orig, "you", "ye");
    orig = replace(orig, "His", "'is");
    orig = replace(orig, " his", " 'is");
    orig = replace(orig, " him", " 'im");
    orig = replace(orig, "Her", "'er");
    orig = replace(orig, " her", " 'er");
    orig = replace(orig, " my", " me");
    orig = replace(orig, "Are", "Be");
    orig = replace(orig, " are", " be");
    orig = replace(orig, " and", " 'n");
    orig = replace(orig, "Is", "Be");
    orig = replace(orig, " is ", " be ");
    orig = replace(orig, " is.", " be.");
    orig = replace(orig, "Of", "O'");
    orig = !rn2(2) ? replace(orig, " of ", " o' ") : orig;
    orig = replace(orig, " to ", rn2(5) ? " to " : " t' ");
    orig = replace(orig, " for", " fer");
    orig = replace(orig, "What ", "Wha' ");
    orig = replace(orig, "what ", "wha' ");
    orig = replace(orig, "with ", "wit' ");
    orig = replace(orig, "With", "Wit'");
    orig = replace(orig, " have", " 'ave");
    orig = replace(orig, "Not ", "Nah ");
    orig = replace(orig, "not ", "nah ");
    orig = replace(orig, " eye ", " deadlight ");
    orig = replace(orig, " eye.", " deadlight.");
    orig = replace(orig, " eye!", " deadlight!");
    orig = replace(orig, " eyes", " deadlights");
    orig = replace(orig, "zorkmid", "doubloon");
    orig = replace(orig, "Zorkmid", "Doubloon");
    orig = replace(orig, "gold coins", "pieces of eight");
    orig = replace(orig, "Gold coins", "Pieces of eight");
    orig = replace(orig, "gold coin", "piece of eight");
    orig = replace(orig, "Gold coin", "Piece of eight");
    orig = replace(orig, "gold pieces", "pieces of eight");
    orig = replace(orig, "Gold pieces", "Pieces of eight");
    orig = replace(orig, "gold piece", "piece of eight");
    orig = replace(orig, "Gold piece", "Piece of eight");
    orig = replace(orig, "treasure", "booty");
    orig = replace(orig, "potion", "bottle");
    orig = replace(orig, "Ouch!", "Arrr!");
    orig = replace(orig, "Wow!", "Avast!");
    orig = replace(orig, "Dumb", "Squiffy");
    
    orig = replace(orig, "state", "way");
    orig = replace(orig, "boy ", "whelp");
    orig = replace(orig, " just", " jus'");
    orig = replace(orig, "before", "'afore");
    orig = replace(orig, "Before", "'Afore");
    orig = replace(orig, " rear", " aft");
    orig = replace(orig, " bottom", " dungbie");
    orig = replace(orig, "After", "Aft");
    orig = replace(orig, " after", " aft");
    orig = replace(orig, "nothing", "naught");
    orig = replace(orig, "Nothing", "Naught");
    orig = replace(orig, "recorded", "logged");
    orig = replace(orig, "record", "log");
    orig = replace(orig, "careful", "handsome");
    orig = replace(orig, "terrible", "ghastly");
    orig = replace(orig, "quick", "smart");
    orig = replace(orig, "talk", "natter");
    orig = replace(orig, "noises", "racket");
    orig = replace(orig, " lord", " cap'n");
    orig = replace(orig, " killed", 
                   rn2(2) ? " scuttled" : rn2(2) 
                                          ? " killed" : rn2(2) 
                                                ? " sunk" : " cut down");
    orig = replace(orig, "dies ", 
                   rn2(2) ? "walks the plank" : rnd(2) 
                                                ? "dances the hempen jig" : rnd(2) 
                                                      ? "sees the black spot" : "dies");
    orig = replace(orig, "probably", "prolly");
    orig = replace(orig, " own ", " owns ");
    orig = replace(orig, "music ", "chanties ");
    orig = replace(orig, "toilet", "head");
    orig = replace(orig, "knapsack", "duffle");
    orig = replace(orig, "dirty rag", "black jack");
    orig = replace(orig, "succubus", "strumpet");
    orig = replace(orig, "incubus", "rapscallion");
    orig = replace(orig, "scoundrel", "picaroon");
    orig = replace(orig, "Gasp!", "Blimey!");
    orig = replace(orig, "Uh-oh.", "Sink me!");
    orig = replace(orig, "Oh my!", "Shiver me timbers!");
    orig = replace(orig, "What?", "Arr!");
    orig = replace(orig, "Hmmm", "Arr");
    orig = replace(orig, "Hmm", "Arr");
    orig = replace(orig, "Why?", "Scupper that!");
    orig = replace(orig, "Oh no!", "avast ye!");
    orig = replace(orig, "Oh no", "avast ya");
    orig = replace(orig, "services rendered", "crackin' Jenny's tea up");
    orig = replace(orig, "suffocate", "dance with Jack Ketch");
    orig = replace(orig, "fall asleep", "take a chalk");
    orig = replace(orig, "falls asleep", "takes a chalk");
    orig = replace(orig, "wakes up", "shows a leg");
    orig = replace(orig, "wake up", "show a leg");
    orig = replace(orig, "steal ", rn2(3) ? "hornswaggle " : "steal ");
    
    /* This will catch a LOT of stuff */
    orig = replace(orig, "cing ", "cin' ");
    orig = replace(orig, "ding ", "din' ");
    orig = replace(orig, "ging ", "gin' ");
    orig = replace(orig, "king ", "kin' ");
    orig = replace(orig, "ming ", "min' ");
    orig = replace(orig, "ning ", "nin' ");
    orig = replace(orig, "oing ", "oin' ");
    orig = replace(orig, "ting ", "tin' ");
    orig = replace(orig, "ssing ", "ssin' ");
    orig = replace(orig, "ving ", "vin' ");
    orig = replace(orig, "wing ", "win' ");
    orig = replace(orig, "ying ", "yin' ");
    
    return orig;
}

/* keep the most recent DUMPLOG_MSG_COUNT messages */
void
dumplogmsg(line)
const char *line;
{
    /*
     * TODO:
     *  This essentially duplicates message history, which is
     *  currently implemented in an interface-specific manner.
     *  The core should take responsibility for that and have
     *  this share it.
     */
    unsigned indx = saved_pline_index; /* next slot to use */
    char *oldest = saved_plines[indx]; /* current content of that slot */

    if (!strncmp(line, "Unknown command", 15))
        return;

    if (oldest && strlen(oldest) >= strlen(line)) {
        /* this buffer will gradually shrink until the 'else' is needed;
           there's no pressing need to track allocation size instead */
        Strcpy(oldest, line);
    } else {
        if (oldest)
            free((genericptr_t) oldest);
        saved_plines[indx] = dupstr(line);
    }
    saved_pline_index = (indx + 1) % DUMPLOG_MSG_COUNT;
}

/* called during save (unlike the interface-specific message history,
   this data isn't saved and restored); end-of-game releases saved_pline[]
   while writing its contents to the final dump log */
void
dumplogfreemessages()
{
    unsigned indx;

    for (indx = 0; indx < DUMPLOG_MSG_COUNT; ++indx)
        if (saved_plines[indx])
            free((genericptr_t) saved_plines[indx]), saved_plines[indx] = 0;
    saved_pline_index = 0;
}
#endif

/* keeps windowprocs usage out of pline() */
static void
putmesg(line)
const char *line;
{
    int attr = ATR_NONE;

    if ((pline_flags & URGENT_MESSAGE) != 0
        && (windowprocs.wincap2 & WC2_URGENT_MESG) != 0)
        attr |= ATR_URGENT;
    if ((pline_flags & SUPPRESS_HISTORY) != 0
        && (windowprocs.wincap2 & WC2_SUPPRESS_HIST) != 0)
        attr |= ATR_NOHISTORY;

    putstr(WIN_MESSAGE, attr, line);
}

/* Note that these declarations rely on knowledge of the internals
 * of the variable argument handling stuff in "tradstdc.h"
 */

#if defined(USE_STDARG) || defined(USE_VARARGS)
static void FDECL(vpline, (const char *, va_list));

/*VARARGS1*/
void
pline
VA_DECL(const char *, line)
{
    VA_START(line);
    VA_INIT(line, char *);
    vpline(line, VA_ARGS);
    VA_END();
}

# ifdef USE_STDARG
static void
vpline(const char *line, va_list the_args)
# else
static void
vpline(line, the_args)
const char *line;
va_list the_args;
# endif

#else /* USE_STDARG | USE_VARARG */

# define vpline pline

/*VARARGS1*/
void
pline
VA_DECL(const char *, line)
#endif /* USE_STDARG | USE_VARARG */
{       /* start of vpline() or of nested block in USE_OLDARG's pline() */
    static int in_pline = 0;
    char pbuf[BIGBUFSZ]; /* will get chopped down to BUFSZ-1 if longer */
    int ln;
    int msgtyp;
#if !defined(NO_VSNPRINTF)
    int vlen UNUSED;
#endif
    boolean no_repeat;
    /* Do NOT use VA_START and VA_END in here... see above */

    if (!line || !*line)
        return;
#ifdef HANGUPHANDLING
    if (program_state.done_hup)
        return;
#endif
    if (program_state.wizkit_wishing)
        return;

    if (index(line, '%')) {
#if !defined(NO_VSNPRINTF)
        vlen = vsnprintf(pbuf, sizeof pbuf, line, VA_ARGS);
#if (NH_DEVEL_STATUS != NH_STATUS_RELEASED) && defined(DEBUG)
        if (vlen >= (int) sizeof pbuf)
            panic("%s: truncation of buffer at %zu of %d bytes",
                  "pline", sizeof pbuf, vlen);
#endif
#else
        Vsprintf(pbuf, line, VA_ARGS);
#endif
        line = pbuf;
    }
    if ((ln = (int) strlen(line)) > BUFSZ - 1) {
        if (line != pbuf)                          /* no '%' was present */
            (void) strncpy(pbuf, line, BUFSZ - 1); /* caveat: unterminated */
        /* truncate, preserving the final 3 characters:
           "___ extremely long text" -> "___ extremely l...ext"
           (this may be suboptimal if overflow is less than 3) */
        memcpy(pbuf + BUFSZ - 1 - 6, "...", 3);
        /* avoid strncpy; buffers could overlap if excess is small */
        pbuf[BUFSZ - 1 - 3] = line[ln - 3];
        pbuf[BUFSZ - 1 - 2] = line[ln - 2];
        pbuf[BUFSZ - 1 - 1] = line[ln - 1];
        pbuf[BUFSZ - 1] = '\0';
        line = pbuf;
    }

#if defined(DUMPLOG) || defined(DUMPHTML)
    /* We hook here early to have options-agnostic output.
     * Unfortunately, that means Norep() isn't honored (general issue) and
     * that short lines aren't combined into one longer one (tty behavior).
     */
    if ((pline_flags & SUPPRESS_HISTORY) == 0)
        dumplogmsg(line);
#endif

    if (Role_if(PM_PIRATE)){
        line = piratesay(line);
    }

    /* use raw_print() if we're called too early (or perhaps too late
       during shutdown) or if we're being called recursively (probably
       via debugpline() in the interface code) */
    if (in_pline++ || !iflags.window_inited) {
        /* [we should probably be using raw_printf("\n%s", line) here] */
        raw_print(line);
        iflags.last_msg = PLNMSG_UNKNOWN;
        goto pline_done;
    }

    msgtyp = MSGTYP_NORMAL;
    no_repeat = (pline_flags & PLINE_NOREPEAT) ? TRUE : FALSE;
    if ((pline_flags & OVERRIDE_MSGTYPE) == 0) {
        msgtyp = msgtype_type(line, no_repeat);
        if ((pline_flags & URGENT_MESSAGE) == 0
            && (msgtyp == MSGTYP_NOSHOW
                || (msgtyp == MSGTYP_NOREP && !strcmp(line, prevmsg))))
            /* FIXME: we need a way to tell our caller that this message
             * was suppressed so that caller doesn't set iflags.last_msg
             * for something that hasn't been shown, otherwise a subsequent
             * message which uses alternate wording based on that would be
             * doing so out of context and probably end up seeming silly.
             * (Not an issue for no-repeat but matters for no-show.)
             */
            goto pline_done;
    }

    if (vision_full_recalc)
        vision_recalc(0);
    if (u.ux)
        flush_screen(1); /* %% */

    putmesg(line);

#if defined(MSGHANDLER) && (defined(POSIX_TYPES) || defined(__GNUC__))
    execplinehandler(line);
#endif

    /* this gets cleared after every pline message */
    iflags.last_msg = PLNMSG_UNKNOWN;
    (void) strncpy(prevmsg, line, BUFSZ), prevmsg[BUFSZ - 1] = '\0';
    switch (msgtyp) {
    case MSGTYP_ALERT:
        iflags.msg_is_alert = TRUE; /* <TAB> */
        /*FALLTHRU*/
    case MSGTYP_STOP:
        display_nhwindow(WIN_MESSAGE, TRUE); /* --more-- */
        break;
    }
    iflags.msg_is_alert = FALSE;

 pline_done:
    --in_pline;
    return;

#if !(defined(USE_STDARG) || defined(USE_VARARGS))
    /* provide closing brace for the nested block
       which immediately follows USE_OLDARGS's VA_DECL() */
    VA_END();
#endif
}

/* pline() variant which can override MSGTYPE handling or suppress
   message history (tty interface uses pline() to issue prompts and
   they shouldn't be blockable via MSGTYPE=hide) */
/*VARARGS2*/
void custompline
VA_DECL2(unsigned, pflags, const char *, line)
{
    VA_START(line);
    VA_INIT(line, const char *);
    pline_flags = pflags;
    vpline(line, VA_ARGS);
    pline_flags = 0;
    VA_END();
    return;
}

/*VARARGS1*/
void Norep
VA_DECL(const char *, line)
{
    VA_START(line);
    VA_INIT(line, const char *);
    pline_flags = PLINE_NOREPEAT;
    vpline(line, VA_ARGS);
    pline_flags = 0;
    VA_END();
    return;
}

/* work buffer for You(), &c and verbalize() */
static char *you_buf = 0;
static int you_buf_siz = 0;

static char *
You_buf(siz)
int siz;
{
    if (siz > you_buf_siz) {
        if (you_buf)
            free((genericptr_t) you_buf);
        you_buf_siz = siz + 10;
        you_buf = (char *) alloc((unsigned) you_buf_siz);
    }
    return you_buf;
}

void
free_youbuf()
{
    if (you_buf)
        free((genericptr_t) you_buf), you_buf = (char *) 0;
    you_buf_siz = 0;
}

/* `prefix' must be a string literal, not a pointer */
#define YouPrefix(pointer, prefix, text) \
    Strcpy((pointer = You_buf((int) (strlen(text) + sizeof prefix))), prefix)

#define YouMessage(pointer, prefix, text) \
    strcat((YouPrefix(pointer, prefix, text), pointer), text)

/*VARARGS1*/
void You
VA_DECL(const char *, line)
{
    char *tmp;

    VA_START(line);
    VA_INIT(line, const char *);
    vpline(YouMessage(tmp, "You ", line), VA_ARGS);
    VA_END();
}

/*VARARGS1*/
void Your
VA_DECL(const char *, line)
{
    char *tmp;

    VA_START(line);
    VA_INIT(line, const char *);
    vpline(YouMessage(tmp, "Your ", line), VA_ARGS);
    VA_END();
}

/*VARARGS1*/
void You_feel
VA_DECL(const char *, line)
{
    char *tmp;

    VA_START(line);
    VA_INIT(line, const char *);
    if (Unaware)
        YouPrefix(tmp, "You dream that you feel ", line);
    else
        YouPrefix(tmp, "You feel ", line);
    vpline(strcat(tmp, line), VA_ARGS);
    VA_END();
}

/*VARARGS1*/
void You_cant
VA_DECL(const char *, line)
{
    char *tmp;

    VA_START(line);
    VA_INIT(line, const char *);
    vpline(YouMessage(tmp, "You can't ", line), VA_ARGS);
    VA_END();
}

/*VARARGS1*/
void pline_The
VA_DECL(const char *, line)
{
    char *tmp;

    VA_START(line);
    VA_INIT(line, const char *);
    vpline(YouMessage(tmp, "The ", line), VA_ARGS);
    VA_END();
}

/*VARARGS1*/
void There
VA_DECL(const char *, line)
{
    char *tmp;

    VA_START(line);
    VA_INIT(line, const char *);
    vpline(YouMessage(tmp, "There ", line), VA_ARGS);
    VA_END();
}

/*VARARGS1*/
void You_hear
VA_DECL(const char *, line)
{
    char *tmp;

    if (Deaf || !flags.acoustics)
        return;
    VA_START(line);
    VA_INIT(line, const char *);
    if (Underwater)
        YouPrefix(tmp, "You barely hear ", line);
    else if (Unaware)
        YouPrefix(tmp, "You dream that you hear ", line);
    else
        YouPrefix(tmp, "You hear ", line);  /* Deaf-aware */
    vpline(strcat(tmp, line), VA_ARGS);
    VA_END();
}

/*VARARGS1*/
void You_see
VA_DECL(const char *, line)
{
    char *tmp;

    VA_START(line);
    VA_INIT(line, const char *);
    if (Unaware)
        YouPrefix(tmp, "You dream that you see ", line);
    else if (Blind) /* caller should have caught this... */
        YouPrefix(tmp, "You sense ", line);
    else
        YouPrefix(tmp, "You see ", line);
    vpline(strcat(tmp, line), VA_ARGS);
    VA_END();
}

/* Print a message inside double-quotes.
 * The caller is responsible for checking deafness.
 * Gods can speak directly to you in spite of deafness.
 */
/*VARARGS1*/
void verbalize
VA_DECL(const char *, line)
{
    char *tmp;

    VA_START(line);
    VA_INIT(line, const char *);
    tmp = You_buf((int) strlen(line) + sizeof "\"\"");
    Strcpy(tmp, "\"");
    Strcat(tmp, line);
    Strcat(tmp, "\"");
    vpline(tmp, VA_ARGS);
    VA_END();
}

/*VARARGS1*/
/* Note that these declarations rely on knowledge of the internals
 * of the variable argument handling stuff in "tradstdc.h"
 */

#if defined(USE_STDARG) || defined(USE_VARARGS)
static void FDECL(vraw_printf, (const char *, va_list));

void raw_printf
VA_DECL(const char *, line)
{
    VA_START(line);
    VA_INIT(line, char *);
    vraw_printf(line, VA_ARGS);
    VA_END();
}

# ifdef USE_STDARG
static void
vraw_printf(const char *line, va_list the_args)
# else
static void
vraw_printf(line, the_args)
const char *line;
va_list the_args;
# endif

#else /* USE_STDARG | USE_VARARG */

void raw_printf
VA_DECL(const char *, line)
#endif
{
    char pbuf[BIGBUFSZ]; /* will be chopped down to BUFSZ-1 if longer */
    /* Do NOT use VA_START and VA_END in here... see above */

    if (index(line, '%')) {
#if !defined(NO_VSNPRINTF)
        (void) vsnprintf(pbuf, sizeof pbuf, line, VA_ARGS);
#else
        Vsprintf(pbuf, line, VA_ARGS);
#endif
        line = pbuf;
    }
    if ((int) strlen(line) > BUFSZ - 1) {
        if (line != pbuf)
            line = strncpy(pbuf, line, BUFSZ - 1);
        /* unlike pline, we don't futz around to keep last few chars */
        pbuf[BUFSZ - 1] = '\0'; /* terminate strncpy or truncate vsprintf */
    }
    raw_print(line);
#if defined(MSGHANDLER) && (defined(POSIX_TYPES) || defined(__GNUC__))
    execplinehandler(line);
#endif
#if !(defined(USE_STDARG) || defined(USE_VARARGS))
    VA_END(); /* (see vpline) */
#endif
}

/*VARARGS1*/
void impossible
VA_DECL(const char *, s)
{
    char pbuf[BIGBUFSZ]; /* will be chopped down to BUFSZ-1 if longer */

    VA_START(s);
    VA_INIT(s, const char *);
    if (program_state.in_impossible)
        panic("impossible called impossible");

    program_state.in_impossible = 1;
#if !defined(NO_VSNPRINTF)
    (void) vsnprintf(pbuf, sizeof pbuf, s, VA_ARGS);
#else
    Vsprintf(pbuf, s, VA_ARGS);
#endif
    pbuf[BUFSZ - 1] = '\0'; /* sanity */
    paniclog("impossible", pbuf);
    if (iflags.debug_fuzzer)
        panic("%s", pbuf);
    pline("%s", VA_PASS1(pbuf));
    /* reuse pbuf[] */
    Strcpy(pbuf, "Program in disorder!");
    if (program_state.something_worth_saving)
        Strcat(pbuf, "  (Saving and reloading may fix this problem.)");
    pline("%s", VA_PASS1(pbuf));

    program_state.in_impossible = 0;
    VA_END();
}

#if defined(MSGHANDLER) && (defined(POSIX_TYPES) || defined(__GNUC__))
static boolean use_pline_handler = TRUE;

static void
execplinehandler(line)
const char *line;
{
    int f;
    const char *args[3];
    char *env;

    if (!use_pline_handler)
        return;

    if (!(env = nh_getenv("NETHACK_MSGHANDLER"))) {
        use_pline_handler = FALSE;
        return;
    }

    f = fork();
    if (f == 0) { /* child */
        args[0] = env;
        args[1] = line;
        args[2] = NULL;
        (void) setgid(getgid());
        (void) setuid(getuid());
        (void) execv(args[0], (char *const *) args);
        perror((char *) 0);
        (void) fprintf(stderr, "Exec to message handler %s failed.\n", env);
        nh_terminate(EXIT_FAILURE);
    } else if (f > 0) {
        int status;

        waitpid(f, &status, 0);
    } else if (f == -1) {
        perror((char *) 0);
        use_pline_handler = FALSE;
        pline("%s", VA_PASS1("Fork to message handler failed."));
    }
}
#endif /* MSGHANDLER && (POSIX_TYPES || __GNUC__) */

/*
 * varargs handling for files.c
 */
#if defined(USE_STDARG) || defined(USE_VARARGS)
static void FDECL(vconfig_error_add, (const char *, va_list));

/*VARARGS1*/
void
config_error_add
VA_DECL(const char *, str)
{
    VA_START(str);
    VA_INIT(str, char *);
    vconfig_error_add(str, VA_ARGS);
    VA_END();
}

# ifdef USE_STDARG
static void
vconfig_error_add(const char *str, va_list the_args)
# else
static void
vconfig_error_add(str, the_args)
const char *str;
va_list the_args;
# endif

#else /* !(USE_STDARG || USE_VARARG) => USE_OLDARGS */

/*VARARGS1*/
void
config_error_add
VA_DECL(const char *, str)
#endif /* ?(USE_STDARG || USE_VARARG) */
{       /* start of vconf...() or of nested block in USE_OLDARG's conf...() */
#if !defined(NO_VSNPRINTF)
    int vlen UNUSED;
#endif
    char buf[BIGBUFSZ]; /* will be chopped down to BUFSZ-1 if longer */

#if !defined(NO_VSNPRINTF)
    vlen = vsnprintf(buf, sizeof buf, str, VA_ARGS);
#if (NH_DEVEL_STATUS != NH_STATUS_RELEASED) && defined(DEBUG)
    if (vlen >= (int) sizeof buf)
        panic("%s: truncation of buffer at %zu of %d bytes",
              "config_error_add", sizeof buf, vlen);
#endif
#else
    Vsprintf(buf, str, VA_ARGS);
#endif
    buf[BUFSZ - 1] = '\0';
    config_erradd(buf);

#if !(defined(USE_STDARG) || defined(USE_VARARGS))
    VA_END(); /* (see pline/vpline -- ends nested block for USE_OLDARGS) */
#endif
}

/*pline.c*/
