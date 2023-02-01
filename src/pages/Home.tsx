import { 
  IonContent, 
  IonHeader, 
  IonPage, 
  IonTitle, 
  IonToolbar,
  IonItemGroup,
  IonItemDivider,
  IonItem,
  IonLabel,
  useIonAlert } from '@ionic/react';
import './Home.css';

import { useHistory } from 'react-router';

import { ImageResultsRepository } from '../utils/ImageRepository';
import { BarcodeRepository } from '../utils/BarcodeRepository';

import ScanbotSdk, { 
  DocumentScannerConfiguration, 
  BarcodeScannerConfiguration} from 'cordova-plugin-scanbot-sdk';

const Home: React.FC = () => {

  const history = useHistory();
  const [presentAlert] = useIonAlert();

  // scan document SDK feature
  const startDocumentScanner = async () => {
  
    const configs: DocumentScannerConfiguration = {
      cameraPreviewMode: 'FIT_IN',
      interfaceOrientation: 'PORTRAIT',
      pageCounterButtonTitle: '%d Page(s)',
      multiPageEnabled: true,
      ignoreBadAspectRatio: true,
      topBarBackgroundColor: '#c8193c',
      bottomBarBackgroundColor: '#c8193c',
      // see further configs ...
    };
    
    await ScanbotSdk.UI.startDocumentScanner(async (documentScannerResult) => {

        if (documentScannerResult.status === 'CANCELED') {
          // user has canceled the scanning operation
          return;
        } 

        await ImageResultsRepository.INSTANCE.addPages(documentScannerResult.pages);

        history.push("/imagepreview");

    }, 
    (error) => {
      // error handeling call back you can add your logic here
      presentAlert({
        header: 'Error',
        message: error.message,
        buttons: ['OK'],
      })
    }, {uiConfigs: configs});
  }

  // scan barcode
  const scanBarcode = async () => {
    const configs: BarcodeScannerConfiguration = {
      // Customize colors, text resources, behavior, etc..
      finderTextHint: 'Please align the barcode or QR code in the frame above to scan it.',
      interfaceOrientation: 'PORTRAIT',
      finderLineColor: '#0000ff',
      barcodeFormats: BarcodeRepository.getAcceptedTypes(), // optional filter for specific barcode types
      // see further configs ...
    };

    await ScanbotSdk.UI.startBarcodeScanner((barcodeResults) => {
      let barcodeString:string = '';
      if(barcodeResults.status == "CANCELED") return;

      if(barcodeResults.barcodes == undefined) return;

      barcodeResults.barcodes.forEach(barcode => {
        barcodeString += barcode.type + ' : ' + barcode.text + '\n';
      });

      presentAlert({
        header: 'Barcode Results',
        message: barcodeString,
        buttons: ['OK'],
      })
    }, 
    (error) => {
      presentAlert({
        header: 'Error',
        message: error.message,
        buttons: ['OK'],
      })
    }, 
    {uiConfigs: configs})
  }

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Scanbot SDK</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>Document Scan Feature</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async () => { await startDocumentScanner();}}>
            <IonLabel>Scan Document</IonLabel>
          </IonItem>
          <IonItem onClick={() => { history.push("/imagepreview"); }}>
            <IonLabel>View Images</IonLabel>
          </IonItem>
        </IonItemGroup>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>Barcode Scan Feature</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async() => {await scanBarcode()}}>
            <IonLabel>Scan Barcode</IonLabel>
          </IonItem>
        </IonItemGroup>

      </IonContent>
    </IonPage>
  );
};

export default Home;