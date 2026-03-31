#include <gtk/gtk.h>
#include <gtk-layer-shell.h>
#include <webkit2/webkit2.h>
#include <glib.h>

static gboolean on_decide_policy(WebKitWebView *web_view, WebKitPolicyDecision *decision, WebKitPolicyDecisionType decision_type, gpointer user_data) {
    if (decision_type != WEBKIT_POLICY_DECISION_TYPE_NAVIGATION_ACTION) {
        return FALSE;
    }

    WebKitNavigationPolicyDecision *navigation_decision = WEBKIT_NAVIGATION_POLICY_DECISION(decision);
    WebKitNavigationAction *action = webkit_navigation_policy_decision_get_navigation_action(navigation_decision);
    WebKitURIRequest *request = webkit_navigation_action_get_request(action);
    const gchar *uri = webkit_uri_request_get_uri(request);

    if (g_str_has_prefix(uri, "http://") || g_str_has_prefix(uri, "https://")) {
        GError *error = NULL;
        g_app_info_launch_default_for_uri(uri, NULL, &error);
        if (error != NULL) {
            g_warning("Erro ao abrir URI %s: %s", uri, error->message);
            g_error_free(error);
        }
        webkit_policy_decision_ignore(decision);
        return TRUE;
    }

    return FALSE;
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);

    // Initialize on layer shell
    gtk_layer_init_for_window(GTK_WINDOW(window));
    gtk_layer_set_layer(GTK_WINDOW(window), GTK_LAYER_SHELL_LAYER_BACKGROUND);

    // Full screen
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);

    // Ignorer input
    gtk_layer_set_keyboard_mode(GTK_WINDOW(window), GTK_LAYER_SHELL_KEYBOARD_MODE_NONE);

    WebKitWebView *webview = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Conecta handler de navegação para abrir links no navegador padrão
    g_signal_connect(webview, "decide-policy", G_CALLBACK(on_decide_policy), NULL);

    const char *home = g_getenv("HOME");
    if (home != NULL) {
        gchar *html_path = g_build_filename(home, ".config", "wallpaper", "index.html", NULL);
        gchar *html_uri = g_filename_to_uri(html_path, NULL, NULL);

        if (html_uri != NULL) {
            webkit_web_view_load_uri(webview, html_uri);
            g_free(html_uri);
        }

        g_free(html_path);
    }

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));
    gtk_widget_show(GTK_WIDGET(webview));

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("team.lilcode.wallhtml", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}