import { Redirect, Route } from 'react-router-dom';
import { IonApp, IonRouterOutlet, setupIonicReact } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';
import Home from './pages/Home';
import ImagePreview from './pages/ImagePreview';
import ImageEditView from './pages/ImageEditView';

/* Core CSS required for Ionic components to work properly */
import '@ionic/react/css/core.css';

/* Basic CSS for apps built with Ionic */
import '@ionic/react/css/normalize.css';
import '@ionic/react/css/structure.css';
import '@ionic/react/css/typography.css';

/* Optional CSS utils that can be commented out */
import '@ionic/react/css/padding.css';
import '@ionic/react/css/float-elements.css';
import '@ionic/react/css/text-alignment.css';
import '@ionic/react/css/text-transformation.css';
import '@ionic/react/css/flex-utils.css';
import '@ionic/react/css/display.css';

/* Theme variables */
import './theme/variables.css';

/* Scanbot SDK */
import ScanbotSdk, { ScanbotSDKConfiguration } from 'cordova-plugin-scanbot-sdk';

setupIonicReact();

// initialize Scanbot SDK
const initializeSdk = async () =>
{
    const config: ScanbotSDKConfiguration = {
        loggingEnabled: true,
        licenseKey: '',
    };
    try {
        ScanbotSdk.initializeSdk(
          (result) => {
          if (result.status == "OK"){
            console.log('Scanbot SDK Initialized');
          }
         },
         (error) => { 
          console.log(error.message);
         },
         config);
    } catch (e) {
        console.error(e);
    }
}

const App: React.FC = () => {

  initializeSdk();

  return (
    <IonApp>
      <IonReactRouter>
        <IonRouterOutlet>
          <Route exact path="/home">
            <Home />
          </Route>
          <Route exact path="/">
            <Redirect to="/home" />
          </Route>
          <Route exact path="/imagepreview">
            <ImagePreview />
          </Route>
            <Route exact path="/imageeditview/:pageId" component={ImageEditView}>
          </Route>
        </IonRouterOutlet>
      </IonReactRouter>
    </IonApp>
  );
}

export default App;