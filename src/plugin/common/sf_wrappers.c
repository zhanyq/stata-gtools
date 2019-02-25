/**
 * @file st_gentools.c
 * @version 0.3.0
 * @author Mauricio Caceres Bravo
 * @email <mauricio.caceres.bravo@gmail.com>
 * @date 27 Oct 2017
 * @brief General-purpose utility functions for writing Stata plugins
 *
 * These are various wrappers to make it easier to write Stata plugins.
 * Note because functions are for use by Stata C-based plugins they
 * must be used in conjunction with stplugin.c and stplugin.h (see
 * stata.com/plugins for more on Stata plugins). In particular, both
 * should exist in the same directory and your main file should have
 *
 *     #include "stplugin.h"
 *
 * as one of its include statements.
 *
 * @see http://www.stata.com/plugins for more on Stata plugins
 */

#include "sf_wrappers.h"
#include "sf_printf.c"

/**
 * @brief Read scalar into unsigned integer
 *
 * @param st_scalar name of Stata scalar
 * @param sval Scalar value
 * @return Read scalar into GT_size variable
 */
ST_retcode sf_scalar_size (char *st_scalar, GT_size *sval)
{
    ST_retcode rc = 0;
    ST_double _double;
    if ( (rc = SF_scal_use(st_scalar, &_double)) ) {
        return (rc);
    }
    else {
        *sval = (GT_size) _double;
    }
    return (rc);
}

/**
 * @brief Get length of Stata vector
 *
 * @param st_matrix name of Stata vector (1xN or Nx1)
 * @return Return number of rows or cols.
 */
GT_int sf_get_vector_length (char *st_matrix)
{
    GT_int ncol = SF_col(st_matrix);
    GT_int nrow = SF_row(st_matrix);
    if ( (ncol > 1) & (nrow > 1) ) {
        sf_errprintf("tried to get the length a "GT_size_cfmt" by "GT_size_cfmt" matrix\n", nrow, ncol);
        return (-1);
    }
    return ( ncol > nrow? ncol: nrow );
}

/**
 * @brief Parse stata vector into C array
 *
 * @param st_matrix name of stata matrix to get
 * @param v array where to store the vector
 * @return Store min and max of @x
 */
ST_retcode sf_get_vector (char *st_matrix, ST_double *v)
{
    ST_retcode rc = 0;

    GT_size i;
    GT_size ncol = SF_col(st_matrix);
    GT_size nrow = SF_row(st_matrix);
    if ( (ncol > 1) & (nrow > 1) ) {
        sf_errprintf("tried to read a "GT_size_cfmt" by "GT_size_cfmt" matrix into an array\n", nrow, ncol);
        return (198);
    }

    if ( ncol > 1 ) {
        for (i = 0; i < ncol; i++) {
            if ( (rc = SF_mat_el(st_matrix, 1, i + 1, v + i)) )
                return (rc);
        }
    }
    else {
        for (i = 0; i < nrow; i++) {
            if ( (rc = SF_mat_el(st_matrix, i + 1, 1, v + i)) )
                return (rc);
        }
    }

    return (rc);
}

/**
 * @brief Parse stata vector into C array
 *
 * @param st_matrix name of stata matrix to get
 * @param v array where to store the vector
 * @return Store min and max of @x
 */
ST_retcode sf_get_vector_int (char *st_matrix, GT_int *v)
{
    ST_double z;
    ST_retcode rc = 0;

    GT_size i;
    GT_size ncol = SF_col(st_matrix);
    GT_size nrow = SF_row(st_matrix);
    if ( (ncol > 1) & (nrow > 1) ) {
        sf_errprintf("tried to read a "GT_size_cfmt" by "GT_size_cfmt" matrix into an array\n", nrow, ncol);
        return (198);
    }
    else if ( (ncol == 0) & (nrow == 0) ) {
        sf_errprintf("tried to read a "GT_size_cfmt" by "GT_size_cfmt" matrix into an array\n", nrow, ncol);
        return (198);
    }

    if ( ncol > 1 ) {
        for (i = 0; i < ncol; i++) {
            if ( (rc = SF_mat_el(st_matrix, 1, i + 1, &z)) ) return (rc);
            v[i] = (GT_int) z;
        }
    }
    else {
        for (i = 0; i < nrow; i++) {
            if ( (rc = SF_mat_el(st_matrix, i + 1, 1, &z)) ) return (rc);
            v[i] = (GT_int) z;
        }
    }

    return (rc);
}

/**
 * @brief Parse stata vector into C array
 *
 * @param st_matrix name of stata matrix to get
 * @param v array where to store the vector
 * @return Store min and max of @x
 */
ST_retcode sf_get_vector_size (char *st_matrix, GT_size *v)
{
    ST_double z;
    ST_retcode rc = 0;

    GT_size i;
    GT_size ncol = SF_col(st_matrix);
    GT_size nrow = SF_row(st_matrix);
    if ( (ncol > 1) & (nrow > 1) ) {
        sf_errprintf("tried to read a "GT_size_cfmt" by "GT_size_cfmt" matrix into an array\n", nrow, ncol);
        return (198);
    }
    else if ( (ncol == 0) & (nrow == 0) ) {
        sf_errprintf("tried to read a "GT_size_cfmt" by "GT_size_cfmt" matrix into an array\n", nrow, ncol);
        return (198);
    }

    if ( ncol > 1 ) {
        for (i = 0; i < ncol; i++) {
            if ( (rc = SF_mat_el(st_matrix, 1, i + 1, &z)) ) return (rc);
            v[i] = (GT_size) z;
        }
    }
    else {
        for (i = 0; i < nrow; i++) {
            if ( (rc = SF_mat_el(st_matrix, i + 1, 1, &z)) ) return (rc);
            v[i] = (GT_size) z;
        }
    }

    return (rc);
}

/**
 * @brief Parse stata vector into C array
 *
 * @param st_matrix name of stata matrix to get
 * @param v array where to store the vector
 * @return Store min and max of @x
 */
ST_retcode sf_get_vector_bool (char *st_matrix, GT_bool *v)
{
    ST_double z;
    ST_retcode rc = 0;

    GT_size i;
    GT_size ncol = SF_col(st_matrix);
    GT_size nrow = SF_row(st_matrix);
    if ( (ncol > 1) & (nrow > 1) ) {
        sf_errprintf("tried to read a "GT_size_cfmt" by "GT_size_cfmt" matrix into an array\n", nrow, ncol);
        return (198);
    }
    else if ( (ncol == 0) & (nrow == 0) ) {
        sf_errprintf("tried to read a "GT_size_cfmt" by "GT_size_cfmt" matrix into an array\n", nrow, ncol);
        return (198);
    }

    if ( ncol > 1 ) {
        for (i = 0; i < ncol; i++) {
            if ( (rc = SF_mat_el(st_matrix, 1, i + 1, &z)) ) return (rc);
            v[i] = (GT_bool) z;
        }
    }
    else {
        for (i = 0; i < nrow; i++) {
            if ( (rc = SF_mat_el(st_matrix, i + 1, 1, &z)) ) return (rc);
            v[i] = (GT_bool) z;
        }
    }

    return (rc);
}

/*********************************************************************
 *                           Stata helpers                           *
 *********************************************************************/

/**
 * @brief Wrapper for OOM error exit message
 */
ST_retcode sf_oom_error (char *step_desc, char *obj_desc)
{
    sf_errprintf ("%s: Unable to allocate memory for object '%s'.\n", step_desc, obj_desc);
    SF_display ("See {help gcollapse##memory:help gcollapse (Out of memory)}.\n");
    return (1702);
}

/*********************************************************************
 *                          Stata utilities                          *
 *********************************************************************/

/**
 * @brief Update a running timer and print a message to satata console
 *
 * Prints a messasge to Stata that the running timer @timer was last set
 * @diff seconds ago. It then updates the timer to the current time.
 *
 * @param timer clock object containing time since last udpate
 * @param msg message to print before # of seconds
 * @return Print time since last update to Stata console
 */
void sf_running_timer (clock_t *timer, const char *msg)
{
    double diff  = (double) (clock() - *timer) / CLOCKS_PER_SEC;
    sf_printf (msg);
    sf_printf (" (%.3f seconds).\n", diff);
    *timer = clock();
}

/**
 * @brief Check if in returns at least some observations
 *
 * @return 1 if at least 1 obs; 0 otherwise
 */
GT_size sf_anyobs_sel()
{
    GT_size i;
    for (i = SF_in1(); i <= SF_in2(); i++)
        if ( SF_ifobs(i) ) return(i);

    return (0);
}

/*********************************************************************
 *                          Misc utilities                           *
 *********************************************************************/

void sf_format_size(GT_size n, char *out)
{
    int c;
    char buf[32];
    char *p;

    sprintf(buf, GT_size_cfmt, n);
    c = 2 - strlen(buf) % 3;
    for (p = buf; *p != 0; p++) {
       *out++ = *p;
       if (c == 1) {
           *out++ = ',';
           // *out++ = ',';
       }
       c = (c + 1) % 3;
    }
    *--out = 0;
}

/**
 * @brief Write by variables to disk
 * @param st_info object with meta info
 * @return Saves by variables in disk
 */
ST_retcode sf_byx_save (struct StataInfo *st_info)
{
    char GTOOLS_BYVAR_FILE[st_info->gfile_byvar];
    char GTOOLS_BYCOL_FILE[st_info->gfile_bycol];
    FILE *fbyvar;
    FILE *fbycol;

    ST_retcode rc = 0;
    ST_double z;
    GT_size k, total;
    GT_size kvars    = st_info->kvars_by;
    GT_size anychar  = (st_info->kvars_by_str > 0);
    GT_size rowbytes = (st_info->rowbytes + sizeof(GT_size));
    ST_double anydbl = (ST_double) anychar;
    ST_double jdbl   = (ST_double) st_info->J;
    ST_double kdbl   = (ST_double) kvars + 1;

    if ( (kvars > 0) && (st_info->J > 0) && (st_info->Nread > 0) ) {

        if ( (rc = SF_macro_use("GTOOLS_BYVAR_FILE", GTOOLS_BYVAR_FILE, st_info->gfile_byvar) )) goto exit;
        if ( (rc = SF_macro_use("GTOOLS_BYCOL_FILE", GTOOLS_BYCOL_FILE, st_info->gfile_bycol) )) goto exit;

        fbyvar = fopen(GTOOLS_BYVAR_FILE, "wb");
        fbycol = fopen(GTOOLS_BYCOL_FILE, "wb");

        rc = rc | (fwrite(&anydbl, sizeof(ST_double), 1, fbycol) != 1);
        rc = rc | (fwrite(&jdbl,   sizeof(ST_double), 1, fbycol) != 1);
        rc = rc | (fwrite(&kdbl,   sizeof(ST_double), 1, fbycol) != 1);

        if ( anychar ) {
            z  = (ST_double) rowbytes;
            rc = rc | (fwrite(&z, sizeof(ST_double), 1, fbycol) != 1);
            z  = (ST_double) st_info->kvars_by_num;
            rc = rc | (fwrite(&z, sizeof(ST_double), 1, fbycol) != 1);
            z  = (ST_double) st_info->kvars_by_str;
            rc = rc | (fwrite(&z, sizeof(ST_double), 1, fbycol) != 1);

            for (k = 0; k < kvars; k++) {
                z  = (ST_double) st_info->byvars_lens[k];
                rc = rc | (fwrite(&z, sizeof(ST_double), 1, fbycol) != 1);
            }

            total = st_info->J * rowbytes;
            rc = rc | (fwrite(st_info->st_by_charx, sizeof(st_info->st_by_charx), total, fbyvar) != total);
        }
        else {
            total = st_info->J * (kvars + 1);
            rc = rc | (fwrite(st_info->st_by_numx, sizeof(st_info->st_by_numx), total, fbyvar) != total);
        }

        fclose (fbyvar);
        fclose (fbycol);
    }

exit:
    return (rc);
}
