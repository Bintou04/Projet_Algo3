#include "gui.h"
#include "support.h"
#include <string.h>
#include <stdlib.h>

/* Variables globales */
static Element **listeGlobale;
static GtkWidget *zoneAffichage;
static GtkWidget *entryId;
static GtkWidget *entryTitre;
static GtkWidget *entryModule;

/* CSS moderne */
static const char *CSS_STYLE = 
    "window {"
    "    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);"
    "}"
    ".card {"
    "    background: white;"
    "    border-radius: 15px;"
    "    padding: 25px;"
    "    box-shadow: 0 10px 40px rgba(0,0,0,0.1);"
    "}"
    "entry {"
    "    border: 2px solid #e0e0e0;"
    "    border-radius: 8px;"
    "    padding: 12px 15px;"
    "    font-size: 14px;"
    "    min-height: 40px;"
    "    background: white;"
    "}"
    "entry:focus {"
    "    border-color: #667eea;"
    "    box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1);"
    "}"
    ".btn-primary {"
    "    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);"
    "    color: white;"
    "    border: none;"
    "    border-radius: 8px;"
    "    padding: 12px 24px;"
    "    font-weight: bold;"
    "    font-size: 14px;"
    "    min-height: 45px;"
    "}"
    ".btn-primary:hover {"
    "    background: linear-gradient(135deg, #5568d3 0%, #6a3f8f 100%);"
    "    box-shadow: 0 5px 15px rgba(102, 126, 234, 0.3);"
    "}"
    ".btn-danger {"
    "    background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);"
    "    color: white;"
    "    border: none;"
    "    border-radius: 8px;"
    "    padding: 12px 24px;"
    "    font-weight: bold;"
    "    font-size: 14px;"
    "    min-height: 45px;"
    "}"
    ".btn-danger:hover {"
    "    background: linear-gradient(135deg, #e082ea 0%, #e4465b 100%);"
    "}"
    ".btn-success {"
    "    background: linear-gradient(135deg, #43e97b 0%, #38f9d7 100%);"
    "    color: white;"
    "    border: none;"
    "    border-radius: 8px;"
    "    padding: 12px 24px;"
    "    font-weight: bold;"
    "    font-size: 14px;"
    "    min-height: 45px;"
    "}"
    ".btn-success:hover {"
    "    background: linear-gradient(135deg, #32d86a 0%, #27e8c6 100%);"
    "}"
    ".btn-info {"
    "    background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%);"
    "    color: white;"
    "    border: none;"
    "    border-radius: 8px;"
    "    padding: 12px 24px;"
    "    font-weight: bold;"
    "    font-size: 14px;"
    "    min-height: 45px;"
    "}"
    ".btn-info:hover {"
    "    background: linear-gradient(135deg, #3e9bed 0%, #00e1ed 100%);"
    "}"
    "textview {"
    "    border: 2px solid #e0e0e0;"
    "    border-radius: 8px;"
    "    padding: 15px;"
    "    font-family: 'Consolas', monospace;"
    "    font-size: 13px;"
    "    background: #f8f9fa;"
    "}"
    "label {"
    "    color: #2c3e50;"
    "    font-weight: 600;"
    "    font-size: 13px;"
    "}";

/* ==================== AFFICHER ==================== */
void on_afficher_clicked(GtkWidget *widget, gpointer data) {
    char buffer[4096] = "";
    Element *tmp = *listeGlobale;
    
    if (tmp == NULL) {
        strcpy(buffer, "📋 Aucun support enregistré\n");
    } else {
        strcat(buffer, "═══════════════════════════════════════════════\n");
        strcat(buffer, "           📚 LISTE DES SUPPORTS\n");
        strcat(buffer, "═══════════════════════════════════════════════\n\n");
        
        while (tmp != NULL) {
            char ligne[512];
            sprintf(ligne, "🔹 ID: %d\n   Titre: %s\n   Module: %s\n\n",
                    tmp->support.id,
                    tmp->support.titre,
                    tmp->support.module);
            strcat(buffer, ligne);
            tmp = tmp->suivant;
        }
    }

    gtk_text_buffer_set_text(
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage)),
        buffer,
        -1
    );
}

/* ==================== AJOUTER ==================== */
void on_ajouter_clicked(GtkWidget *widget, gpointer data) {
    Support s;
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entryId));
    const char *titre_text = gtk_entry_get_text(GTK_ENTRY(entryTitre));
    const char *module_text = gtk_entry_get_text(GTK_ENTRY(entryModule));

    if (strlen(id_text) == 0 || strlen(titre_text) == 0 || strlen(module_text) == 0) {
        gtk_text_buffer_set_text(
            gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage)),
            "❌ Erreur: Veuillez remplir tous les champs",
            -1
        );
        return;
    }

    s.id = atoi(id_text);
    strcpy(s.titre, titre_text);
    strcpy(s.module, module_text);

    *listeGlobale = ajouterSupport(*listeGlobale, s);
    
    // Vider les champs
    gtk_entry_set_text(GTK_ENTRY(entryId), "");
    gtk_entry_set_text(GTK_ENTRY(entryTitre), "");
    gtk_entry_set_text(GTK_ENTRY(entryModule), "");
    
    gtk_text_buffer_set_text(
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage)),
        "✅ Support ajouté avec succès!",
        -1
    );
}

/* ==================== SUPPRIMER ==================== */
void on_supprimer_clicked(GtkWidget *widget, gpointer data) {
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entryId));
    
    if (strlen(id_text) == 0) {
        gtk_text_buffer_set_text(
            gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage)),
            "❌ Erreur: Veuillez entrer un ID",
            -1
        );
        return;
    }
    
    int id = atoi(id_text);
    *listeGlobale = supprimerSupport(*listeGlobale, id);
    
    gtk_entry_set_text(GTK_ENTRY(entryId), "");
    
    gtk_text_buffer_set_text(
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage)),
        "🗑️  Support supprimé",
        -1
    );
}

/* ==================== RECHERCHER ==================== */
void on_rechercher_clicked(GtkWidget *widget, gpointer data) {
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entryId));
    
    if (strlen(id_text) == 0) {
        gtk_text_buffer_set_text(
            gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage)),
            "❌ Erreur: Veuillez entrer un ID",
            -1
        );
        return;
    }
    
    int id = atoi(id_text);
    Element *res = rechercherSupport(*listeGlobale, id);

    if (res != NULL) {
        char msg[512];
        sprintf(msg, "🔍 RÉSULTAT DE LA RECHERCHE\n\n"
                     "ID: %d\n"
                     "Titre: %s\n"
                     "Module: %s\n",
                res->support.id,
                res->support.titre,
                res->support.module);

        gtk_text_buffer_set_text(
            gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage)),
            msg,
            -1
        );
    } else {
        gtk_text_buffer_set_text(
            gtk_text_view_get_buffer(GTK_TEXT_VIEW(zoneAffichage)),
            "❌ Support non trouvé",
            -1
        );
    }
}

/* ==================== GUI PRINCIPALE ==================== */
void lancerGUI(int argc, char *argv[], Element **liste) {
    GtkWidget *fenetre, *mainBox, *card, *grid, *scrolled;
    GtkWidget *btnAjouter, *btnSupprimer, *btnRechercher, *btnAfficher;
    GtkWidget *labelId, *labelTitre, *labelModule, *labelTitle;
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    listeGlobale = liste;

    gtk_init(&argc, &argv);

    // Appliquer le CSS
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen,
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_data(provider, CSS_STYLE, -1, NULL);
    g_object_unref(provider);

    // Fenêtre principale
    fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetre), "Gestion des Supports");
    gtk_window_set_default_size(GTK_WINDOW(fenetre), 700, 600);
    gtk_container_set_border_width(GTK_CONTAINER(fenetre), 30);
    g_signal_connect(fenetre, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Box principale
    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(fenetre), mainBox);

    // Card (conteneur blanc)
    card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_name(card, "card");
    gtk_style_context_add_class(gtk_widget_get_style_context(card), "card");
    gtk_container_set_border_width(GTK_CONTAINER(card), 25);
    gtk_box_pack_start(GTK_BOX(mainBox), card, TRUE, TRUE, 0);

    // Titre
    labelTitle = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(labelTitle), 
                        "<span size='x-large' weight='bold'>📚 Gestion des Supports</span>");
    gtk_box_pack_start(GTK_BOX(card), labelTitle, FALSE, FALSE, 10);

    // Grid pour les champs
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 15);
    gtk_box_pack_start(GTK_BOX(card), grid, FALSE, FALSE, 0);

    // Labels et entries
    labelId = gtk_label_new("🔢 ID:");
    gtk_widget_set_halign(labelId, GTK_ALIGN_START);
    entryId = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryId), "Entrez l'ID du support");
    gtk_widget_set_hexpand(entryId, TRUE);

    labelTitre = gtk_label_new("📖 Titre:");
    gtk_widget_set_halign(labelTitre, GTK_ALIGN_START);
    entryTitre = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryTitre), "Entrez le titre du support");
    gtk_widget_set_hexpand(entryTitre, TRUE);

    labelModule = gtk_label_new("📚 Module:");
    gtk_widget_set_halign(labelModule, GTK_ALIGN_START);
    entryModule = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryModule), "Entrez le nom du module");
    gtk_widget_set_hexpand(entryModule, TRUE);

    gtk_grid_attach(GTK_GRID(grid), labelId, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryId, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), labelTitre, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryTitre, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), labelModule, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryModule, 1, 2, 1, 1);

    // Boutons avec styles
    GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(buttonBox), TRUE);
    gtk_box_pack_start(GTK_BOX(card), buttonBox, FALSE, FALSE, 10);

    btnAjouter = gtk_button_new_with_label("➕ Ajouter");
    gtk_style_context_add_class(gtk_widget_get_style_context(btnAjouter), "btn-primary");
    
    btnSupprimer = gtk_button_new_with_label("🗑️  Supprimer");
    gtk_style_context_add_class(gtk_widget_get_style_context(btnSupprimer), "btn-danger");
    
    btnRechercher = gtk_button_new_with_label("🔍 Rechercher");
    gtk_style_context_add_class(gtk_widget_get_style_context(btnRechercher), "btn-info");
    
    btnAfficher = gtk_button_new_with_label("📋 Afficher Tout");
    gtk_style_context_add_class(gtk_widget_get_style_context(btnAfficher), "btn-success");

    gtk_box_pack_start(GTK_BOX(buttonBox), btnAjouter, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(buttonBox), btnSupprimer, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(buttonBox), btnRechercher, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(buttonBox), btnAfficher, TRUE, TRUE, 0);

    // Zone d'affichage avec scroll
    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_vexpand(scrolled, TRUE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    
    zoneAffichage = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(zoneAffichage), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(zoneAffichage), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled), zoneAffichage);
    gtk_box_pack_start(GTK_BOX(card), scrolled, TRUE, TRUE, 0);

    // Connecter les signaux
    g_signal_connect(btnAjouter, "clicked", G_CALLBACK(on_ajouter_clicked), NULL);
    g_signal_connect(btnSupprimer, "clicked", G_CALLBACK(on_supprimer_clicked), NULL);
    g_signal_connect(btnRechercher, "clicked", G_CALLBACK(on_rechercher_clicked), NULL);
    g_signal_connect(btnAfficher, "clicked", G_CALLBACK(on_afficher_clicked), NULL);

    gtk_widget_show_all(fenetre);
    gtk_main();
}