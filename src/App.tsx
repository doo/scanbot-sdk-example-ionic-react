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

import React from "react";
import DocumentScannerPage from './pages/features/document_detectors/DocumentScannerPage';
import BarcodeScannerPage from './pages/features/barcode_detectors/BarcodeScannerPage';
import DataDetectorPage from './pages/features/data_detectors/DataDetectorPage';
import ScanbotService from './services/scanbot_service';
import BarcodeResultPage from './pages/features/barcode_detectors/BarcodeResultPage';
import MRZResultPage from './pages/features/data_detectors/MRZResultPage';
import EHICResultPage from './pages/features/data_detectors/EHICResultPage';
import CheckResultPage from './pages/features/data_detectors/CheckResultPage';
import MedicalCertificateResultPage from './pages/features/data_detectors/MedicalCertificateResultPage';

setupIonicReact();

const App: React.FC = () => {

  ScanbotService.initSdk();

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
          <Route exact path="/document_scanner/:selectedItem" component={DocumentScannerPage}>
          </Route>
          <Route exact path="/barcode_scanner/:selectedItem" component={BarcodeScannerPage}>
          </Route>
          <Route exact path="/data_detector/:selectedItem" component={DataDetectorPage}>
          </Route>
          <Route exact path="/imagepreview">
            <ImagePreview />
          </Route>
          <Route exact path="/barcode_result">
            <BarcodeResultPage />
          </Route>
          <Route exact path="/mrz_result" component={MRZResultPage}>
          </Route>
          <Route exact path="/ehic_result" component={EHICResultPage}>
          </Route>
          <Route exact path="/check_result" component={CheckResultPage}>
          </Route>
          <Route exact path="/medical_certificate_result" component={MedicalCertificateResultPage}>
          </Route>
          <Route exact path="/imageeditview/:pageId" component={ImageEditView}>
          </Route>

        </IonRouterOutlet>
      </IonReactRouter>
    </IonApp>
  );
}

export default App;