// Shipeng Xu
// billhsu.x@gmail.com

#include "StateSelectPlane.h"
#include "StateDraw.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/Camera/Camera.h"
#include "Core/UI/UI.h"
#include "Core/UI/UIButton.h"

std::vector<Vector3> StateSelectPlane::selectedPoints;

StateSelectPlane::StateSelectPlane()
{
    stateID = STATE_SELECT_PLANE;
    selectedPoints.clear();
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    selectPlaneMode = SELECT_HORIZONTAL_PLANE;
    btnCancelPlane = Controller::GUI->addButton(stateID*100 + BTN_ID_CANCEL_PLANE, "BTN_ID_CANCEL_PLANE", btnCancelPlaneEvent);
    btnCancelPlane->setVisibility(false);
    btnConfirmPlane = Controller::GUI->addButton(stateID*100 + BTN_ID_CONFIRM_PLANE, "BTN_ID_CONFIRM_PLANE", btnConfirmPlaneEvent);
    btnConfirmPlane->setVisibility(false);
    btnSelectHorizontalPlane = Controller::GUI->addButton(stateID*100 + BTN_ID_SELECT_HORIZONTAL, "BTN_ID_SELECT_HORIZONTAL", btnSelectHorizontalPlaneEvent);
    btnSelectHorizontalPlane->setVisibility(false);
    btnSelectVerticalPlane = Controller::GUI->addButton(stateID*100 + BTN_ID_SELECT_VERTICAL, "BTN_ID_SELECT_VERTICAL", btnSelectVerticalPlaneEvent);
    btnSelectVerticalPlane->setVisibility(false);
}

void StateSelectPlane::buildCurrentPlane()
{
    Vector3 planeVec = Vector3(0, 1, 0);
    if(selectedPoints.size() == 1) 
    {
        if(selectPlaneMode == SELECT_VERTICAL_PLANE)
        {
            planeVec = mCamera->getDirection();
            planeVec.y = 0;
            planeVec.normalize();
        }
        else if (selectPlaneMode == SELECT_HORIZONTAL_PLANE)
        {
            planeVec = Vector3(0, 1, 0);
        }
    }
    else if(selectedPoints.size() == 2)
    {
        if(selectPlaneMode == SELECT_VERTICAL_PLANE)
        {
            planeVec = Vector3(0, 1, 0);
        }
        else if (selectPlaneMode == SELECT_SLOPE)
        {
            planeVec = Controller::getInstance().getCameraRay().GetDirection();
            planeVec.y = 0;
            planeVec = planeVec.cross(Vector3(0, 1, 0));
            planeVec.normalize();
        }
    }
    Plane::buildPlane(selectedPoints, Controller::currPlane, planeVec);
    if(Controller::currPlane.N.dot(mCamera->getDirection())>0)
    {
        Controller::currPlane = - Controller::currPlane;
    }
}

void StateSelectPlane::MouseButton(int button, int state, int x, int y)
{
    if(button == Mouse::MOUSE_SCROLL)
    {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
    if(state == Mouse::MOUSE_DOWN)
    {
        if(button == Mouse::MOUSE_LEFT)
        {
            Vector3 v;
            Controller::getInstance().getCameraPoint(v, Controller::currPlane, Camera::GETPOINT_PLANE);
            std::cout<<v<<std::endl;
            // three selected points should be different 
            for(int i=0; i<selectedPoints.size();++i) 
            {
                if(v==selectedPoints[i]) return;
            }
            selectedPoints.push_back(v);
            if(selectedPoints.size() == 2)
            {
                selectPlaneMode = SELECT_VERTICAL_PLANE;
            }
            buildCurrentPlane();
            Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
                                          Quaternion::Z_NEG_AXIS);
            mCamera->rotateCamTo(q);
            Controller::currPlane.printStatus();
            
            Vector3 center(0,0,0);
            for(int i=0;i<selectedPoints.size();++i)
                center += selectedPoints[i];
            center /= selectedPoints.size();

            mCamera->setCamCenterTo(center);
            if(selectedPoints.size()==3) 
            {
                dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->vCenter = center;
                dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->selectedPoints = selectedPoints;
                enterState(State::statePool[STATE_DRAW]);
            }
        }
    }
}

void StateSelectPlane::MouseRightDrag(int dx, int dy)
{
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}


void StateSelectPlane::Keyboard(unsigned char key, unsigned char status)
{
    if(status == Controller::KEY_UP)
    {
        if(key == 13)
        {
            Vector3 center(0,0,0);
            for(int i=0;i<selectedPoints.size();++i)
                center += selectedPoints[i];
            center /= selectedPoints.size();
            
            dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->vCenter = center;
            dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->selectedPoints = selectedPoints;
            enterState(State::statePool[STATE_DRAW]);
        }
    }
}
void StateSelectPlane::prepareState()
{
    btnSelectVerticalPlane->appearIn();
    btnSelectHorizontalPlane->appearIn();
    btnConfirmPlane->appearIn();
    btnCancelPlane->appearIn();
}

void StateSelectPlane::btnCancelPlaneEvent(UINode* Sender)
{
    std::cout<<"btnCancelPlaneEvent"<<std::endl;
}
void StateSelectPlane::btnConfirmPlaneEvent(UINode* Sender)
{
    std::cout<<"btnConfirmPlaneEvent"<<std::endl;
}
void StateSelectPlane::btnSelectVerticalPlaneEvent(UINode* Sender)
{
    std::cout<<"btnSelectVerticalPlaneEvent"<<std::endl;
}
void StateSelectPlane::btnSelectHorizontalPlaneEvent(UINode* Sender)
{
    std::cout<<"btnSelectHorizontalPlaneEvent"<<std::endl;
}