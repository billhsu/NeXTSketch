window_width = 800
window_height = 600
--------------------
BTN_LEFT_MARGIN_LEFT = 10
BTN_LEFT_MARGIN_TOP = 80
BTN_LEFT_INTERVAL_VERTICAL = 50
BTN_ID_DOC_NEW = {
   pos = {x="BTN_LEFT_MARGIN_LEFT", y="BTN_LEFT_MARGIN_TOP"},
   textures = {idle = "media/textures/button_document_new.png", hover = "media/textures/button_document_new.png", press = "media/textures/button_document_new.png"},
   size = {width="40", height="40"},
   text = "New Sketch"
}

BTN_ID_DOC_OPEN = {
    pos = {x="BTN_LEFT_MARGIN_LEFT", y="BTN_LEFT_MARGIN_TOP + BTN_LEFT_INTERVAL_VERTICAL"},
    textures = {idle = "media/textures/button_document_open.png", hover = "media/textures/button_document_open.png", press = "media/textures/button_document_open.png"},
    size = {width="40", height="40"},
    text = "Open Sketch"
}

BTN_ID_DOC_SAVE = {
    pos = {x="BTN_LEFT_MARGIN_LEFT", y="BTN_LEFT_MARGIN_TOP + BTN_LEFT_INTERVAL_VERTICAL * 2"},
    textures = {idle = "media/textures/button_document_save.png", hover = "media/textures/button_document_save.png", press = "media/textures/button_document_save.png"},
    size = {width="40", height="40"},
    text = "Save Sketch"
}
--------------------
BTN_ID_SELECT_VERTICAL = {
    pos = {x="window_width / 2 - BTN_ID_SELECT_VERTICAL.size.width / 2 - BTN_ID_SELECT_VERTICAL.size.width", y="window_height - 2 * BTN_ID_SELECT_VERTICAL.size.height"},
    textures = {idle = "media/textures/button_vertical.png", hover = "media/textures/button_vertical.png", press = "media/textures/button_vertical.png"},
    size = {width="60", height="60"},
    text = "Select Vertical Plane"
}

BTN_ID_SELECT_HORIZONTAL = {
    pos = {x="window_width / 2 - BTN_ID_SELECT_HORIZONTAL.size.width / 2 + BTN_ID_SELECT_HORIZONTAL.size.width", y="window_height - 2 * BTN_ID_SELECT_HORIZONTAL.size.height"},
    textures = {idle = "media/textures/button_horizontal.png", hover = "media/textures/button_horizontal.png", press = "media/textures/button_horizontal.png"},
    size = {width="60", height="60"},
    text = "Select Horizontal Plane"
}
--------------------
BTN_ID_CONFIRM_PLANE = {
    pos = {x="BTN_ID_CONFIRM_PLANE.size.width / 2", y="window_height - 2 * BTN_ID_CONFIRM_PLANE.size.height"},
    textures = {idle = "media/textures/button_confirm.png", hover = "media/textures/button_confirm.png", press = "media/textures/button_confirm.png"},
    size = {width="60", height="60"},
    text = "Confirm"
}

BTN_ID_CANCEL_PLANE = {
    pos = {x="BTN_ID_CANCEL_PLANE.size.width / 2 + BTN_ID_CANCEL_PLANE.size.width * 1.2", y="window_height - 2 * BTN_ID_CANCEL_PLANE.size.height"},
    textures = {idle = "media/textures/button_cancel.png", hover = "media/textures/button_cancel.png", press = "media/textures/button_cancel.png"},
    size = {width="60", height="60"},
    text = "Cancel"
}
--------------------
BTN_ID_DRAW_PLANE_DONE = {
    pos = {x="window_width - BTN_ID_DRAW_PLANE_DONE.size.width * 2", y="window_height - 2 * BTN_ID_DRAW_PLANE_DONE.size.height"},
    textures = {idle = "media/textures/button_confirm.png", hover = "media/textures/button_confirm.png", press = "media/textures/button_confirm.png"},
    size = {width="60", height="60"},
    text = "Done"
}

BTN_ID_DELETE_LINE_DONE = {
    pos = {x="window_width - BTN_ID_DELETE_LINE_DONE.size.width * 2", y="window_height - 2 * BTN_ID_DELETE_LINE_DONE.size.height"},
    textures = {idle = "media/textures/button_confirm.png", hover = "media/textures/button_confirm.png", press = "media/textures/button_confirm.png"},
    size = {width="60", height="60"},
    text = "Done"
}
--------------------
BTN_ID_STANDARD_VIEW = {
    pos = {x="window_width / 2 - BTN_ID_STANDARD_VIEW.size.width * 2 * 1.2 - BTN_ID_STANDARD_VIEW.size.width * 0.5", y="BTN_ID_STANDARD_VIEW.size.height / 2"},
    textures = {idle = "media/textures/button_standard_view.png", hover = "media/textures/button_standard_view.png", press = "media/textures/button_standard_view.png"},
    size = {width="60", height="60"},
    text = "Standard view"
}

BTN_ID_UNDO = {
    pos = {x="window_width / 2 - BTN_ID_UNDO.size.width * 1.2 - BTN_ID_UNDO.size.width * 0.5", y="BTN_ID_UNDO.size.height / 2"},
    textures = {idle = "media/textures/button_undo.png", hover = "media/textures/button_undo.png", press = "media/textures/button_undo.png"},
    size = {width="60", height="60"},
    text = "Undo"
}

BTN_ID_REDO = {
    pos = {x="window_width / 2 - BTN_ID_REDO.size.width * 0.5", y="BTN_ID_REDO.size.height / 2"},
    textures = {idle = "media/textures/button_redo.png", hover = "media/textures/button_redo.png", press = "media/textures/button_redo.png"},
    size = {width="60", height="60"},
    text = "Redo"
}

BTN_ID_DELETE_LINE = {
    pos = {x="window_width / 2 + BTN_ID_DELETE_LINE.size.width * 1.2 - BTN_ID_DELETE_LINE.size.width * 0.5", y="BTN_ID_DELETE_LINE.size.height / 2"},
    textures = {idle = "media/textures/button_delete.png", hover = "media/textures/button_delete.png", press = "media/textures/button_delete.png"},
    size = {width="60", height="60"},
    text = "Delete line"
}

BTN_ID_MIRROR = {
    pos = {x="window_width / 2 + BTN_ID_STANDARD_VIEW.size.width * 2 * 1.2 - BTN_ID_STANDARD_VIEW.size.width * 0.5", y="BTN_ID_MIRROR.size.height / 2"},
    textures = {idle = "media/textures/button_mirror.png", hover = "media/textures/button_mirror.png", press = "media/textures/button_mirror.png"},
    size = {width="60", height="60"},
    text = "Mirror mode"
}

--------------------
BTN_MIRROR_SIZE = 64
BTN_ID_MIRROR_Y = {
    pos = {x="window_width / 2 - BTN_MIRROR_SIZE * 0.5", y="window_height / 2 - BTN_MIRROR_SIZE * 1.2"},
    textures = {idle = "media/textures/y_axis.png", hover = "media/textures/y_axis.png", press = "media/textures/y_axis.png"},
    size = {width="BTN_MIRROR_SIZE", height="BTN_MIRROR_SIZE"},
    text = "Mirror Y axis"
}

BTN_ID_MIRROR_Z = {
    pos = {x="window_width / 2 - BTN_MIRROR_SIZE * 1.5", y="window_height / 2 + BTN_MIRROR_SIZE * 0.6"},
    textures = {idle = "media/textures/z_axis.png", hover = "media/textures/z_axis.png", press = "media/textures/z_axis.png"},
    size = {width="BTN_MIRROR_SIZE", height="BTN_MIRROR_SIZE"},
    text = "Mirror Z axis"
}

BTN_ID_MIRROR_X = {
    pos = {x="window_width / 2 + BTN_MIRROR_SIZE * 0.5", y="window_height / 2 + BTN_MIRROR_SIZE * 0.6"},
    textures = {idle = "media/textures/x_axis.png", hover = "media/textures/x_axis.png", press = "media/textures/x_axis.png"},
    size = {width="BTN_MIRROR_SIZE", height="BTN_MIRROR_SIZE"},
    text = "Mirror X axis"
}

BTN_ID_MIRROR_NONE = {
    pos = {x="window_width / 2 - BTN_MIRROR_SIZE * 0.5", y="window_height / 2 + BTN_MIRROR_SIZE * 0"},
    textures = {idle = "media/textures/button_cancel.png", hover = "media/textures/button_cancel.png", press = "media/textures/button_cancel.png"},
    size = {width="BTN_MIRROR_SIZE", height="BTN_MIRROR_SIZE"},
    text = "No mirror"
}